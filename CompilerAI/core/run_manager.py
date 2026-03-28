from core.judge import Judge
from core.code_runner import CodeRunner
from core.models import TestCase, ExecutionResult, ExecutionStatus, AISubmission, ExecutionResultFinal, SingleTestResult, LanguageName
from core.ai_provider import AiProvider
from utils.file_utils import FileUtils
from utils.json_utils import JsonUtils

class RunManager:

    interpretForRet = False

    @classmethod
    def prompt_process(cls, language: LanguageName, prompt: str, attemptNr: int, previous_submission: AISubmission | None = None, previous_result: ExecutionResultFinal | None = None):
        if attemptNr == 0:
            return AiProvider.generate_initial_submission(prompt, language)
        else:
            if previous_submission is None or previous_result is None:
                raise ValueError("Repair submission requires previous submission and previous result.")

            return AiProvider.generate_repair_submission(
                prompt,
                language,
                previous_submission,
                previous_result
            )
        
    @classmethod
    def load_user_testcases(cls, path: str):
        data = JsonUtils.json_to_dict(path)
        raw_tests = data.get("tests", [])
        return [TestCase.from_dict(t) for t in raw_tests]

    @classmethod
    def execution_process(cls, prompt: str, testName: str, language: LanguageName, user_testcases = False,timeout=5):
        attempt = 0
        maxAttempts = 5
        successStop = False

        previous_submission = None
        previous_result = None
        FinalExecution = ExecutionResultFinal(tests=[])
        attempt_history = []

        while attempt < maxAttempts and not successStop:

            if successStop is True:
                break

            successStop = True

            aiSubObj = cls.prompt_process(
                language,
                prompt,
                attempt,
                previous_submission,
                previous_result
            )

            if user_testcases:
                testCaseObjList = cls.load_user_testcases("tasks/echo/user_tests.json")
                aiSubObj.tests = testCaseObjList
            else:
                testCaseObjList = aiSubObj.tests

            FinalExecution = ExecutionResultFinal(tests=[])

            match language:
                case LanguageName.PYTHON:
                    FileUtils.write_to_file("submissions/echo_bad/main.py", aiSubObj.code)
                case LanguageName.CPP:
                    FileUtils.write_to_file("submissions/echo_bad/main.cpp", aiSubObj.code)
                case LanguageName.JAVA:
                    FileUtils.write_to_file("submissions/echo_bad/Main.java", aiSubObj.code)

            for testCaseObj in aiSubObj.tests:
                auxResult = ExecutionResult(
                    status=ExecutionStatus.RUNTIME_ERROR,
                    stdout="",
                    stderr="",
                    exit_code=None,
                    duration_ms=0,
                    timed_out=False
                )

                match language:
                    case LanguageName.PYTHON:
                        auxResult = CodeRunner.execute_command(testCaseObj.stdin, timeout)
                    case LanguageName.CPP:
                        auxResult = CodeRunner.execute_command_cpp(testCaseObj.stdin, timeout)
                    case LanguageName.JAVA:
                        auxResult = CodeRunner.execute_command_java(testCaseObj.stdin, timeout)


                interpret = Judge.interpret_output(testCaseObj.expected_stdout, auxResult)
                cls.interpretForRet = interpret

                if not interpret:
                    successStop = False

                auxSingle = SingleTestResult(
                    test_name=testCaseObj.name,
                    stdin=testCaseObj.stdin,
                    expected_stdout=testCaseObj.expected_stdout,
                    actual_stdout=auxResult.stdout,
                    status=auxResult.status,
                    passed=interpret,
                    stderr=auxResult.stderr,
                    exit_code=auxResult.exit_code,
                    duration_ms=auxResult.duration_ms,
                    timed_out=auxResult.timed_out
                )

                FinalExecution.tests.append(auxSingle)

                resultDict = auxResult.to_dict()
                JsonUtils.dict_to_json(resultDict, f"runs/attempt_{attempt}_intermediate.json")

            attempt_history.append(FinalExecution)

            JsonUtils.dict_to_json(aiSubObj.to_dict(), f"runs/attempt_{attempt}_submission.json")
            JsonUtils.dict_to_json(FinalExecution.to_dict(), f"runs/attempt_{attempt}_result.json")

            previous_submission = aiSubObj
            previous_result = FinalExecution

            attempt += 1

        for auxTest in FinalExecution.tests:
            print(auxTest)
        print(attempt)

        FinalExecutionDict = FinalExecution.to_dict()
        JsonUtils.dict_to_json(FinalExecutionDict, "runs/finalExe.json")

        history_dict = {
            "attempts": [attempt_result.to_dict() for attempt_result in attempt_history]
        }
        JsonUtils.dict_to_json(history_dict, "runs/history.json")



    @classmethod
    def return_interpret(cls):
        return cls.interpretForRet




#### saved the flow before actual ai prompts


     ## last before AI execute proc from jsons

    #  @classmethod
    # def execution_process(cls, prompt: str, testName: str, language: LanguageName, timeout = 5):
    #     attempt = 0
    #     maxAttempts = 5
    #     successStop = False
    #     success = False
    #     result = ExecutionResult(
    #         status=ExecutionStatus.RUNTIME_ERROR,
    #         stdout="",
    #         stderr="",
    #         exit_code=None,
    #         duration_ms=0,
    #         timed_out=False
    #     )

    #     FinalExecution = ExecutionResultFinal(
    #         tests=[]
    #     )

    #     while attempt < maxAttempts and not(successStop):

    #         # if all test pass break
    #         if successStop == True:
    #             break

    #         successStop = True

    #         # to do prompt the apis + parse
    #         aiSubObj = cls.prompt_process(language, "blah", attempt)
    #         testCaseObjList = aiSubObj.tests

    #         finalResult = ExecutionResultFinal(
    #             tests=[]
    #         )

    #         # iteration through test cases
    #         for testCaseObj in testCaseObjList:
    #             # rewrite the code

    #             # default result type
    #             auxResult = ExecutionResult(
    #                 status=ExecutionStatus.RUNTIME_ERROR,
    #                 stdout="",
    #                 stderr="",
    #                 exit_code=None,
    #                 duration_ms=0,
    #                 timed_out=False
    #             )

    #             match language:
    #                 case LanguageName.PYTHON:
    #                     FileUtils.write_to_file("submissions/echo_bad/main.py", aiSubObj.code)
    #                     # input plus exe
    #                     auxResult = CodeRunner.execute_command(testCaseObj.stdin, timeout)
    #                     result = auxResult
    #                 case LanguageName.CPP:
    #                     FileUtils.write_to_file("submissions/echo_bad/main.cpp", aiSubObj.code)
    #                     auxResult = CodeRunner.execute_command_cpp(testCaseObj.stdin, timeout)
    #                     result = auxResult
    #                 case LanguageName.JAVA:
    #                     FileUtils.write_to_file("submissions/echo_bad/Main.java", aiSubObj.code)
    #                     auxResult = CodeRunner.execute_command_java(testCaseObj.stdin, timeout)
    #                     result = auxResult

    #             # input plus exe
    #             # auxResult = CodeRunner.execute_command(testCaseObj.stdin, timeout)
    #             # result = auxResult

    #             # check if output matches expected
    #             interpret = Judge.interpret_output(testCaseObj.expected_stdout,auxResult)
    #             cls.interpretForRet = interpret

    #              # if success stops
    #             if not interpret:
    #                 success = False
    #                 successStop = False
    #             else:
    #                 success = True

    #             # to do generate the json for ai reinterpretation/ final 
    #             auxSingle = SingleTestResult(
    #                 test_name=testName,
    #                 stdin=testCaseObj.stdin,
    #                 expected_stdout=testCaseObj.expected_stdout,
    #                 actual_stdout=auxResult.stdout,
    #                 status=result.status,
    #                 passed=success,
    #                 stderr=auxResult.stderr,
    #                 exit_code=auxResult.exit_code,
    #                 duration_ms=auxResult.duration_ms,
    #                 timed_out=auxResult.timed_out
    #             )

    #             # if not FinalExecution.tests:
    #             #     FinalExecution.tests = [auxSingle]
    #             # else:
    #             FinalExecution.tests.append(auxSingle)

    #             resultDict = result.to_dict()
    #             JsonUtils.dict_to_json(resultDict, "runs/intermediate.json")

    #             # to do resend the json to ai and start again

    #         # next attempt
    #         attempt += 1


    #     for auxTest in FinalExecution.tests:
    #         print(auxTest)
    #     print(attempt)

    #     FinalExecutionDict = FinalExecution.to_dict()
    #     JsonUtils.dict_to_json(FinalExecutionDict, "runs/finalExe.json")

    # @classmethod
    # def prompt_process(cls, language: LanguageName, prompt: str):
        
    #     # prompt to json

    #     # convert from json to AISubmission obj
    #     aiSubmitDict = JsonUtils.json_to_dict("tasks/echo/aiSubmission.json")
    #     aiSubmitAux = AISubmission.from_dict(aiSubmitDict)
        
    #     #testCaseDict = JsonUtils.json_to_dict("tasks/echo/testCase.json")
    #     #testCaseAux = TestCase.from_dict(testCaseDict)

    #     return aiSubmitAux


# @classmethod
#     def prompt_process(cls, prompt: str):
        
#         # prompt to json

#         # convert from json to dict
#         testCaseDict = JsonUtils.json_to_dict("tasks/echo/testCase.json")

#         # to type TestCase

#         testCaseAux = TestCase.from_dict(testCaseDict)

#         return testCaseAux

#     @classmethod
#     def execution_process(cls, prompt: str, timeout = 5):

#         # test_name = ""
#         # expected_stdout = ""
#         # std_in = ""

#         attempt = 0
#         maxAttempts = 5
#         success = False
#         result = ExecutionResult(
#             status=ExecutionStatus.RUNTIME_ERROR,
#             stdout="",
#             stderr="",
#             exit_code=None,
#             duration_ms=0,
#             timed_out=False
#         )

#         while attempt < maxAttempts and not(success):
#             # to do prompt the apis + parse
#             testCaseObj = cls.prompt_process("blah")

#             # rewrite the code
#             FileUtils.write_to_file("submissions/echo_bad/main.py","x = int(input())\nprint(x * 3)")

#             # input plus exe
#             auxResult = CodeRunner.execute_command(testCaseObj.stdin, timeout)
#             result = auxResult

#             # check if output matches expected
#             interpret = Judge.interpret_output(testCaseObj.expected_stdout,auxResult)
#             cls.interpretForRet = interpret

#             # to do generate the json for ai reinterpretation/ final 
#             resultDict = result.to_dict()
#             JsonUtils.dict_to_json(resultDict, "runs/intermediate.json")

#             # if success stops
#             if interpret:
#                 success = True
#                 break

#             # next attempt
#             attempt += 1

#             # to do resend the json to ai and start again


#         # to do recall after interpret or errors and send relevant data, or all actually
#         # testCase = TestCase(
#         #     name = test_name,
#         #     stdin = std_in,
#         #     expected_stdout = expected_stdout
#         # )

#         print(result)
#         print(attempt)