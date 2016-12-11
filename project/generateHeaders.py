#!/usr/bin/python3

INCLUDE_DIR = "include/"
SRC_DIR = "src/"

def include_content(name):
    header = "#ifndef " + name + "\n"
    header += "#define " + name + "\n"
    header += "#endif"
    return header

def src_content(name):
    return "#include \"../" + INCLUDE_DIR + name + ".h\""

if __name__ == '__main__':
    import sys
    for f in sys.argv[1:]:
        print(INCLUDE_DIR + f + ".h")
        file_handler = open(INCLUDE_DIR + f + ".h", "w")
        file_handler.write(include_content(f.upper()))
        print(SRC_DIR + f + ".cpp")
        file_handler = open(SRC_DIR + f + ".cpp", "w")
        file_handler.write(src_content(f))
