from dataclasses import dataclass
from enum import Enum


class ExecutionStatus(Enum):
    SUCCESS = "success"
    COMPILE_ERROR = "compile_error"
    RUNTIME_ERROR = "runtime_error"
    TIMEOUT = "timeout"

class LanguageName(Enum):
    PYTHON = "python"
    CPP = "cpp"
    JAVA = "java"
    


@dataclass
class TestCase:
    name: str
    stdin: str | None
    expected_stdout: str

    def to_dict(self) -> dict:
        return {
            "name": self.name,
            "stdin": self.stdin,
            "expected_stdout": self.expected_stdout
        }
    
    @classmethod
    def from_dict(cls, data: dict):
        return cls(
            name=data.get("name", "unnamed"),
            stdin=data.get("stdin", None),
            expected_stdout=data.get("expected_stdout", "")
        )


@dataclass
class ExecutionResult:
    status: ExecutionStatus
    stdout: str
    stderr: str
    exit_code: int | None
    duration_ms: int
    timed_out: bool

    def to_dict(self) -> dict:
        return {
            "status": self.status.value,
            "stdout": self.stdout,
            "stderr": self.stderr,
            "exit_code": self.exit_code,
            "duration_ms": self.duration_ms,
            "timed_out": self.timed_out
        }
    

@dataclass
class SingleTestResult:
    test_name: str
    stdin: str | None
    expected_stdout: str
    actual_stdout: str
    status: ExecutionStatus
    passed: bool
    stderr: str
    exit_code: int | None
    duration_ms: int
    timed_out: bool

    def to_dict(self) -> dict:
        return {
            "test_name": self.test_name,
            "stdin": self.stdin,
            "expected_stdout": self.expected_stdout,
            "actual_stdout": self.actual_stdout,
            "status": self.status.value,
            "passed": self.passed,
            "stderr": self.stderr,
            "exit_code": self.exit_code,
            "duration_ms": self.duration_ms,
            "timed_out": self.timed_out
        }
    
@dataclass
class ExecutionResultFinal:
    tests: list[SingleTestResult]

    def to_dict(self) -> dict:
        return {
            "tests": [t.to_dict() for t in self.tests]
        }


@dataclass
class AISubmission:
    code: str
    tests: list[TestCase]

    def to_dict(self) -> dict:
        return {
            "code": self.code,
            "tests": [t.to_dict() for t in self.tests]
        }
    
    @classmethod
    def from_dict(cls, data: dict):
        code = data.get("code", "")
        raw_tests = data.get("tests", [])
        tests = [TestCase.from_dict(t) for t in raw_tests]

        return cls(
            code=code,
            tests=tests
        )