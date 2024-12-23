import random
import sympy as sp
import csv

# 定义生成随机数的范围
MIN_VALUE = 0.1
MAX_VALUE = 10.0

# 定义运算符
operators = ['+', '-', '*', '/', '^', 'exp', 'log']

# C 语言 double 类型的最大值
DOUBLE_MAX = 1.8e+308


def random_number():
    """生成一个随机小数"""
    return round(random.uniform(MIN_VALUE, MAX_VALUE), 2)


def random_expression(depth=0):
    """生成随机数学表达式"""
    if depth > 2:
        return random_number()

    # 随机选择一个操作数
    if random.choice([True, False]):
        left = random_expression(depth + 1)
    else:
        left = random_number()

    # 随机选择运算符
    op = random.choice(operators)

    if op in ['exp', 'log']:
        # 对于 exp 和 log，只需要一个操作数
        if op == 'exp':
            return f'exp({left})'
        else:
            return f'log({left})'

    # 随机选择另一个操作数
    if random.choice([True, False]):
        right = random_expression(depth + 1)
    else:
        right = random_number()

    # 处理除法，确保不为零
    if op == '/':
        while right == 0:
            right = random_number()

    # 构造表达式
    return f'({left} {op} {right})'


def eval_expression(expr):
    """计算表达式的值"""
    expr = expr.replace('^', '**')  # 替换 '^' 为 '**' 以适配 Python 语法
    try:
        result = sp.sympify(expr).evalf()  # evalf() 用来计算浮动结果
        if abs(result) > DOUBLE_MAX:
            raise ValueError("Result exceeds double max value")
        result_str = f"{result:.6f}"  # 保留六位小数
        if len(result_str) > 200:
            raise ValueError("Result exceeds 200 characters")
        return result_str
    except Exception as e:
        return None


# 生成数学表达式并保存到 CSV 文件
csv_file = 'math_expressions.csv'

with open(csv_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Expression', 'Result'])  # 写入表头

    count = 0
    while count < 1000:
        expr = random_expression()
        result = eval_expression(expr)
        if result is not None:
            writer.writerow([expr, result])  # 写入表达式和结果
            count += 1

print(f"数学表达式及其结果已保存到 {csv_file}")
