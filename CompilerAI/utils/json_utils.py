import json

class JsonUtils:

    @classmethod
    def dict_to_json(cls, dictIn, path):
        with open(path, "w") as write:
            json.dump(dictIn, write)

    @classmethod
    def json_to_dict(cls, path):
        with open(path, "r") as f:
            data = json.load(f)
        return data
    
    