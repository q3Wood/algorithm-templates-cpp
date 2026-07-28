import os

# 设置你要扫描的代码所在的最外层目录，'.' 表示当前脚本所在的目录
ROOT_DIR = '.'  
# 生成的整合文档的文件名
OUTPUT_FILE = 'My_Template_Dictionary.md'

# 过滤掉不需要打印的文件夹和文件
IGNORE_DIRS = {'.vscode', '.git', '.idea', 'build', '大纲'}
# 只抓取这些后缀的文件，新增了 .md
ALLOWED_EXTS = {'.cpp', '.c', '.java', '.py', '.md'}

def generate_markdown():
    # 使用 utf-8 编码打开输出文件，防止中文乱码
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as outfile:
        
        # 写入文档大标题
        outfile.write('# 算法竞赛代码字典 (Team Reference Document)\n\n')
        
        # os.walk 会自动帮你递归遍历所有的文件夹和子文件夹
        for root, dirs, files in os.walk(ROOT_DIR):
            
            # 过滤掉不需要的文件夹（修改 dirs 会影响 os.walk 的遍历）
            dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
            
            # 对文件夹按拼音/字母排序，让打印出来的目录更规整
            dirs.sort()
            files.sort()
            
            # 找出当前目录下所有符合后缀要求的代码文件
            valid_files = [f for f in files if os.path.splitext(f)[1] in ALLOWED_EXTS]
            
            if not valid_files:
                continue # 如果这个文件夹里没代码，就跳过
                
            # 计算当前所在的文件夹深度，用来决定用几级 Markdown 标题
            rel_path = os.path.relpath(root, ROOT_DIR)
            if rel_path == '.':
                depth = 1
                folder_name = "根目录杂项"
            else:
                depth = rel_path.count(os.sep) + 2 # 子文件夹从二级标题开始
                # 修改这里：使用完整的路径替换掉单一文件夹名，让层级更清晰
                folder_name = rel_path.replace(os.sep, ' / ')
            
            # 根据深度生成 Markdown 标题 (比如 ## 数据结构, ### 线段树)
            heading = '#' * min(depth, 6) # 最多到 6 级标题
            outfile.write(f'{heading} {folder_name}\n\n')
            
            for file in valid_files:
                file_path = os.path.join(root, file)
                file_ext = os.path.splitext(file)[1][1:] # 获取扩展名，如 'cpp'
                
                # 写入文件名作为小标题
                outfile.write(f'**{file}**\n\n')
                
                # 开始写入代码块
                outfile.write(f'```{file_ext}\n')
                try:
                    # 读取 C++ 文件内容并写入
                    with open(file_path, 'r', encoding='utf-8') as infile:
                        outfile.write(infile.read())
                except Exception as e:
                    outfile.write(f'// 读取文件出错: {e}\n')
                outfile.write('\n```\n\n')
                
    print(f'✅ 成功！已将所有代码整合到 {OUTPUT_FILE} 中。')

if __name__ == '__main__':
    generate_markdown()