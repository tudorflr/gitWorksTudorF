import json
import os
from openai import OpenAI

from core.models import AISubmission, ExecutionResultFinal, LanguageName


class AiProvider:
    MODEL = "gpt-5.4-mini"

    @classmethod
    def _get_client(cls) -> OpenAI:
        return OpenAI(api_key=os.environ["OPENAI_API_KEY"])

    @classmethod
    def _language_label(cls, language: LanguageName) -> str:
        return language.value

    @classmethod
    def _parse_submission(cls, content: str) -> AISubmission:
        try:
            data = json.loads(content)
            return AISubmission.from_dict(data)
        except Exception as e:
            raise ValueError(f"Invalid JSON from AI:\n{content}") from e

    @classmethod
    def generate_initial_submission(
        cls,
        prompt: str,
        language: LanguageName,
    ) -> AISubmission:
        client = cls._get_client()

        system_prompt = (
            "Return ONLY valid JSON. "
            "The JSON must have exactly this structure: "
            '{"code":"source code as a string","tests":[{"name":"test name","stdin":"input or null","expected_stdout":"exact expected output"}]}. '
            "No markdown. No explanations."
        )

        user_prompt = (
            f"Language: {cls._language_label(language)}\n"
            f"Task:\n{prompt}"
        )

        response = client.responses.create(
            model=cls.MODEL,
            input=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": user_prompt},
            ],
            text={
                "format": {"type": "json_object"}
            },
        )

        return cls._parse_submission(response.output_text)

    @classmethod
    def generate_repair_submission(
        cls,
        prompt: str,
        language: LanguageName,
        previous_submission: AISubmission,
        previous_result: ExecutionResultFinal,
    ) -> AISubmission:
        client = cls._get_client()

        system_prompt = (
            "Return ONLY valid JSON. "
            "The JSON must have exactly this structure: "
            '{"code":"fixed source code as a string","tests":[{"name":"test name","stdin":"input or null","expected_stdout":"exact expected output"}]}. '
            "No markdown. No explanations."
        )

        user_payload = {
            "language": cls._language_label(language),
            "task": prompt,
            "previous_submission": previous_submission.to_dict(),
            "execution_result": previous_result.to_dict(),
            "instruction": "Fix the code so the failing tests pass.",
        }

        response = client.responses.create(
            model=cls.MODEL,
            input=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": json.dumps(user_payload, indent=2)},
            ],
            text={
                "format": {"type": "json_object"}
            },
        )

        return cls._parse_submission(response.output_text)