import pymysql

db= pymysql.connect(host='localhost',
                     port=3306,
                     user='root',
                     passwd='k1010910',
                     db='iot_club',
                     charset='utf8')

# database를 사용하기 위한 cursor를 세팅합니다.
cursor= db.cursor()

try:
	# SQL query 작성
	sql = """SELECT * FROM mytable"""

	# SQL query 실행
	cursor.execute(sql)

	# SQL query 실행 결과를 가져옴
	result = cursor.fetchall()

	print("Data:\n", result);
finally:
	db.close()
