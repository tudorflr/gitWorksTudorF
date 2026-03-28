import os

class FileUtils:

    @classmethod  # will be used to write to the 2nd main.py too
    def write_to_file(cls, path, str_input):   # "/submissions/echo_bad/main.py"  this way to call for container
        with open(path, 'w') as f:
            f.write(str_input)

