# 条件语句
# a = int(input("输入一个整数"))
# if a % 2 == 0:
#     print(f'{a}是偶数')
# else:
#     print(f'{a}是奇数')

# 多重条件语句
# a = int(input("输入一个整数"))
# if a > 0:
#     print(f'{a}是正数')
# elif a == 0:
#     print(f'是{a}')
# else:
#     print(f'{a}是负数')

# 多元条件
# year = int(input('输入年份'))
# if year %100 == 0:
# 	if year %400 == 0:
# 		print('闰年')
# 	else:
# 		print('是平年')
# elif  year % 4 == 0:
# 	print('是闰年')
# else:
# 	print('是平年')

# pass语句
# a = int(input("请输入一个整数:"))
# if a != 1:
# 	pass
# else:
# 	print("hello")

# while循环
# num = 1
# while num < 11:
# 	print(num)
# 	num += 1

# num = 1
# sum = 0
# while num <= 100:
# 	sum += num
# 	num += 1
# print(sum)

# for循环
# range函数生成迭代，左闭右开
# for i in range(1, 11):
# 	print(i)
# 可以规定步长
# for i in range(0, 11, 2):
# 	print(i)
# 步长可以是负数
# for i in range(10, 0, -1):
# 	print(i)

#continue跳过循环
# for i in range(1, 7):
# 	if i == 3:
# 		continue
# 	print(f'吃了第{i}个包子')
#
# break终止循环
# for i in range(1, 7):
# 	if i == 3:
# 		print('不好吃')
# 		break
# 	print(f'吃了第{i}个包子')

#  输入若干个数字, 求平均值. 使用 "分号" 作为结尾.
# sum = 0
# count = 0
# while True:
# 	num = input('请输入数字')
# 	if num == ';':
# 		break
# 	num = float(num)
# 	sum += num
# 	count += 1
# print(sum / count)

# 三元表达式
x = 4
y = 5
small = x if x < y else y
print(small)