#from flask import Blueprint, request, render_template, flash, redirect, url_for
#from flask import current_app as current_app
from flask import Flask, render_template, request
import dbModule

main = Flask(__name__)

@main.route('/')
def index():
    return render_template('index.html')

# SELECT 함수 예제
@main.route('/select', methods=['POST'])
def select(id=None, name=None, phone=None):
    db_class= dbModule.Database()
    id = request.form['id']
    name = request.form['name']
    phone = request.form['phone']

    sql = "SELECT club FROM iot_club.mytable where id='%s' and name='%s' and phone='%s'" % (id, name, phone)
    try:
        row = db_class.executeAll(sql)
        result = row[0]['club']
    except:
        result = "신청된 동아리 없음"
    finally:
        print(sql)
    return render_template('index.html', resultData=result)

if __name__ == "__main__":
	main.run(debug=True, host='0.0.0.0', port="8080")
