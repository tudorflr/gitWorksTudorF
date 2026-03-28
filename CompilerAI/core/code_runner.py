import subprocess
import time
from core.models import ExecutionResult, ExecutionStatus


class CodeRunner:

    @classmethod
    def execute_command(cls, stdin_data=None, timeout=5):
        start = time.time()

        try:
            result = subprocess.run(
                ["python3", "main.py"],
                cwd="submissions/echo_bad",
                input=stdin_data,
                capture_output=True,
                text=True,
                timeout=timeout
            )

            duration = int((time.time() - start) * 1000)

            status = (
                ExecutionStatus.SUCCESS
                if result.returncode == 0
                else ExecutionStatus.RUNTIME_ERROR
            )

            stdout_text = str(result.stdout)
            stderr_text = str(result.stderr)

            resultExe = ExecutionResult(
                status=status,
                stdout=stdout_text,
                stderr=stderr_text,
                exit_code=result.returncode,
                duration_ms=duration,
                timed_out=False
            )

            return resultExe

        except subprocess.TimeoutExpired as e:
            duration = int((time.time() - start) * 1000)

            timeout_stdout = (
                e.stdout.decode()
                if isinstance(e.stdout, bytes)
                else str(e.stdout or "")
            )

            timeout_stderr = (
                e.stderr.decode()
                if isinstance(e.stderr, bytes)
                else str(e.stderr or "Process timed out")
            )

            resultExe = ExecutionResult(
                status=ExecutionStatus.TIMEOUT,
                stdout=timeout_stdout,
                stderr=timeout_stderr,
                exit_code=None,
                duration_ms=duration,
                timed_out=True
            )

            return resultExe
        
    @classmethod
    def execute_command_cpp(cls, stdin_data=None, timeout=5):
        start = time.time()

        try:
            compile_proc = subprocess.run(
                ["g++", "main.cpp", "-o", "out"],
                cwd="submissions/echo_bad",
                capture_output=True,
                text=True
            )

            if compile_proc.returncode != 0:
                duration = int((time.time() - start) * 1000)

                return ExecutionResult(
                    status=ExecutionStatus.COMPILE_ERROR,
                    stdout=compile_proc.stdout,
                    stderr=compile_proc.stderr,
                    exit_code=compile_proc.returncode,
                    duration_ms=duration,
                    timed_out=False
                )

            run_proc = subprocess.run(
                ["./out"],
                cwd="submissions/echo_bad",
                input=stdin_data,
                capture_output=True,
                text=True,
                timeout=timeout
            )

            duration = int((time.time() - start) * 1000)

            status = (
                ExecutionStatus.SUCCESS
                if run_proc.returncode == 0
                else ExecutionStatus.RUNTIME_ERROR
            )

            return ExecutionResult(
                status=status,
                stdout=run_proc.stdout,
                stderr=run_proc.stderr,
                exit_code=run_proc.returncode,
                duration_ms=duration,
                timed_out=False
            )

        except subprocess.TimeoutExpired as e:
            duration = int((time.time() - start) * 1000)

            timeout_stdout = (
                e.stdout.decode()
                if isinstance(e.stdout, bytes)
                else str(e.stdout or "")
            )

            timeout_stderr = (
                e.stderr.decode()
                if isinstance(e.stderr, bytes)
                else str(e.stderr or "Process timed out")
            )

            return ExecutionResult(
                status=ExecutionStatus.TIMEOUT,
                stdout=timeout_stdout,
                stderr=timeout_stderr,
                exit_code=None,
                duration_ms=duration,
                timed_out=True
            )
        

    @classmethod
    def execute_command_java(cls, stdin_data=None, timeout=5):
        start = time.time()

        try:
            # 1. COMPILE
            compile_proc = subprocess.run(
                ["javac", "Main.java"],
                cwd="submissions/echo_bad",
                capture_output=True,
                text=True
            )

            if compile_proc.returncode != 0:
                duration = int((time.time() - start) * 1000)

                return ExecutionResult(
                    status=ExecutionStatus.COMPILE_ERROR,
                    stdout=compile_proc.stdout,
                    stderr=compile_proc.stderr,
                    exit_code=compile_proc.returncode,
                    duration_ms=duration,
                    timed_out=False
                )

            # 2. RUN
            run_proc = subprocess.run(
                ["java", "Main"],
                cwd="submissions/echo_bad",
                input=stdin_data,
                capture_output=True,
                text=True,
                timeout=timeout
            )

            duration = int((time.time() - start) * 1000)

            status = (
                ExecutionStatus.SUCCESS
                if run_proc.returncode == 0
                else ExecutionStatus.RUNTIME_ERROR
            )

            return ExecutionResult(
                status=status,
                stdout=run_proc.stdout,
                stderr=run_proc.stderr,
                exit_code=run_proc.returncode,
                duration_ms=duration,
                timed_out=False
            )

        except subprocess.TimeoutExpired as e:
            duration = int((time.time() - start) * 1000)

            timeout_stdout = (
                e.stdout.decode()
                if isinstance(e.stdout, bytes)
                else str(e.stdout or "")
            )

            timeout_stderr = (
                e.stderr.decode()
                if isinstance(e.stderr, bytes)
                else str(e.stderr or "Process timed out")
            )

            return ExecutionResult(
                status=ExecutionStatus.TIMEOUT,
                stdout=timeout_stdout,
                stderr=timeout_stderr,
                exit_code=None,
                duration_ms=duration,
                timed_out=True
            )