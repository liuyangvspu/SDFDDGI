import os
import re
engine_name = 'Engine'
engine_dir= engine_name + '\\'

extensions=['.cpp', '.hpp', '.h']
src_files = []
for root, dirs, files in os.walk(engine_dir):
    for file in files:
        for ext in extensions:
            if file.endswith(ext):
                path = os.path.join(root, file)
                path = path.replace(engine_dir, '')
                path = path.replace('\\', '/')
                src_files.append(path)
                print(os.path.join(root, file), '=>', path)


ammend_data = 'add_library(\n\t' + engine_name + ' SHARED \n\t'
for file in src_files:
    ammend_data = ammend_data + file + '\n\t'

print(ammend_data)

cmake_file = open(engine_dir + 'CMakeLists.txt')
data = cmake_file.read();
#data = data.replace('add_library([^)]*)', 'add_library(sup)')
data = re.sub('add_library([^)]*)', ammend_data, data, count = 1, flags = re.DOTALL)

cmake_file = open(engine_dir + 'CMakeLists.txt', 'w')
cmake_file.write(data)
print(data)