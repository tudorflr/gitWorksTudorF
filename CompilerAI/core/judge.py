from core.models import ExecutionResult, ExecutionStatus, TestCase

class Judge:
    

    @classmethod
    def interpret_output(cls, expected_out, result: ExecutionResult):
        if expected_out == result.stdout:  # will improve this, ignore spaces for ints etc
            return True
        else:
            return False