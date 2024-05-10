import os
import re
import zlib

def compress_string(data):
    #return zlib.compress(data.encode())
    return data

def generate_c_files(folder_path, output_file, header_file):
    files = {}
    init_code = ""

    for root, _, files_in_dir in os.walk(folder_path):
        for file_name in files_in_dir:
            file_path = os.path.join(root, file_name)
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
                content = re.sub(r'\s+', ' ', content).strip()

                compressed_content = compress_string(content)

                # Generate variable name from file path
                var_name = file_name.replace('.', '_')

                files[var_name] = compressed_content

                content_type = "text/html"  # Default content type
                if var_name.endswith("_css"):
                    content_type = "text/css"
                elif var_name.endswith("_js"):
                    content_type = "application/javascript"

                init_code += 'server->on("/{}", HTTP_GET, [](AsyncWebServerRequest *request) {{ request->send_P(200, "{}", {}); }});\n'.format(file_name, content_type, var_name)
                if(file_name == "index.html"):
                    #default landing page
                    init_code += 'server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {{ request->send_P(200, "{}", {}); }});\n'.format(content_type, var_name)


    # Generate C file
    with open(output_file, 'w') as f:
        f.write('#include "{}"\n\n'.format(header_file))
        for var_name, content in files.items():
            f.write('const char {}[] PROGMEM = R"rawliteral({})rawliteral";\n\n'.format(var_name, content))
        f.write('void init_web_pages(AsyncWebServer * server) {\n')
        for line in init_code.splitlines():
            f.write("    {}\n".format(line))
        f.write('}\n')


folder_path = 'www'
output_file = 'www.ino'
header_file = 'www.h'
generate_c_files(folder_path, output_file, header_file)