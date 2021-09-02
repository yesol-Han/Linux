use iot_club;
drop table mytable;

create table mytable ( id varchar(8), name varchar(10), phone varchar(20), club varchar(30));

LOAD DATA LOCAL INFILE '/home/pi/IoT_Club/iot_club.csv'
REPLACE INTO TABLE `iot_club`.`mytable`
COLUMNS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
(@id, @name, @phone, @club)
SET `id` = @id, `name` = @name, `phone` = @phone, `club` = @club;

