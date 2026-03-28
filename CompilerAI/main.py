from core.run_manager import RunManager
from core.models import LanguageName

prompt = "Write a program that reads a single integer from standard input and prints the integer multiplied by 3."

RunManager.execution_process(
    prompt,
    "attemptAgain",
    LanguageName.JAVA,
    True
)

interpret = RunManager.return_interpret()
print(f"\n{interpret}")