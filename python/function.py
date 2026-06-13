# 设计一个计算年龄的函数
# def year(x):
# 	return 2026 - x
# print(year(int(input())))

# 位置参数
# def func(name, age, height, weight):
#   print('name =', name)
#   print('age =', age)
#   print('height =', height)
#   print('weight =', weight)
# func('小贝', 18, '155cm', '40kg')

# 关建字参数
# def func(name, age, height, weight):
#   print('name =', name)
#   print('age =', age)
#   print('height =', height)
#   print('weight =', weight)
# func(age = 18, weight = '40kg', name = '小贝', height = '155cm')

# 函数参数支持从尾巴开始缺省值
# def func(name, age, weight, height = '155cm'):
#   print('name =', name)
#   print('age =', age)
#   print('height =', height)
#   print('weight =', weight)
# func('小贝', 18, '40kg')
# func('小贝', 18, '40kg', '158cm')

# 函数支持多返回值，返回的是元组
# def return_menu(food1, food2, food3, food4):
# 	return food1, food2, food3, food4
# print(return_menu('蒸羊羔', '蒸熊掌', '蒸鹿尾儿', '烧花鸭'))

# 函数优先去局部找变量，找不到再去全局，但是全局作用域不刻意访问局部作用域
# def func():
#   value = '我是局部作用域'
#   print(value)
# print(value)

# def func():
# 	# 但是global修饰的变量必须先声明后定义
# 	global value
# 	value = '我是局部作用域'
# 	print(value)
# # 即使加上了global也需要先调用函数才能用
# func()
# print(value)