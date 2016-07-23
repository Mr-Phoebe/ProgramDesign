-- 删除同名表，消除冲突
DROP TABLE login_t;
DROP TABLE customer_t;
DROP TABLE room_t;
DROP TABLE checkin_t;
DROP TABLE evluate_t;
DROP TABLE sum_t;
DROP TABLE time_t;

----------------------------------------
-- 创建登录验证表
----------------------------------------
CREATE TABLE login_t(
	uid			INTEGER PRIMARY KEY,	-- 记录操作员的 id，其实没什么用
	username	TEXT,					-- 记录用户名，实际会限定在20字符以内，这里存储不做限制
	password	TEXT,					-- 记录密码，同上，在输入时作限制
	level 		INTEGER				-- 权限等级
);

-- 插入两条数据作为测试数据，第一行数据来确定其实操作号
INSERT INTO login_t VALUES(101, 'test', 'test', 2);
INSERT INTO login_t VALUES(null, 'whn', 'whn',1);
INSERT INTO login_t VALUES(null, 'admin','admin',0 );


----------------------------------------
-- 创建预定用户信息表
----------------------------------------
CREATE TABLE customer_t(
	cid		INTEGER PRIMARY KEY,	-- 用户的ID号，用于创建外键用
	name	TEXT,					-- 用户姓名，有长度限制，在输入时限制
	sex		INTEGER,				-- 用户性别，0：男，1：女
	id		TEXT,					-- 用户身份证号，有限定，在输入时控制
	phone	TEXT,					-- 用户联系电话，有限定，在输入时控制
	roomnos	TEXT,					-- 用户预定的房号，可以有多个，以空格分隔
	checkintime	DATE				-- 预定入住时间	
);

-- 插入三条测试数据，第一行数据用来确定ID号起始
--INSERT INTO customer_t VALUES(5001, '张三', 0, '42012318985212345', '15822375678', '611 615', date());
--INSERT INTO customer_t VALUES(null, '牛二', 0, '42012218925112343', '15822375221', '619', date());
--INSERT INTO customer_t VALUES(null, '放心奶', 1, '42012218925132351', '16282237522', '712', date());

----------------------------------------
-- 创建入住用户信息表
----------------------------------------
CREATE TABLE checkin_t(
	ciid	INTEGER PRIMARY KEY,	-- 入住用户ID号
	name	TEXT,
	sex		INTEGER,				-- 用户性别，0：男，1：女
	id		TEXT,					-- 用户身份证号，有限定，在输入时控制
	phone	TEXT,					-- 用户联系电话，有限定，在输入时控制
	roomno	INTEGER,				-- 用户入住的房号
	checkintime	DATE				-- 入住时间，一般为当天
);

-- 插入四条测试数据，第一行数据用来确定ID号起始
--INSERT INTO checkin_t VALUES(1001, '潘胜', 0, '42012318985211343', '15823275678', 602, date());
--INSERT INTO checkin_t VALUES(null, '郭燕', 0, '32012218925112343', '18822375221', 603, date());
--INSERT INTO checkin_t VALUES(null, '但丁', 1, '22012218925132351', '18982237522', 702, date());
--INSERT INTO checkin_t VALUES(null, '是你', 1, '22012218925132351', '18982232222', 705, date());

----------------------------------------
-- 创建房屋信息表
----------------------------------------
CREATE TABLE room_t(
	rid			INTEGER PRIMARY KEY,	-- 房屋的ID号，同用户ID一起创建外键用
	roomno		INTEGER,				-- 房屋号，不可更改
	roomtype	INTEGER,				-- 房屋类型，1：单人间，2：双人间，3：三人间 4：豪华间
	status		INTEGER,				-- 房屋状态，1：空闲，2：已预定，3：已入住
	price		INTEGER,					-- 房屋价格，不可更改，默认单人间：240，双人间220，三人间270，豪华间360
	discount	DOUBLE					-- 房屋折扣
);

-- 插入测试房屋数，这里假定共有40间房可供测试使用
-- 25间双人间，10间单人间，5间三人间
-- 601-615为双人间，616-620为三人间
-- 701-710为单人间，711-715为双人间，716-720为豪华间
-- 别问为什么，随便瞎写的
INSERT INTO room_t VALUES(10001, 601, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 602, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 603, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 604, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 605, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 606, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 607, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 608, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 609, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 610, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 611, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 612, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 613, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 614, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 615, 2, 1, 220,1.0);

INSERT INTO room_t VALUES(null, 616, 3, 1, 270,1.0);
INSERT INTO room_t VALUES(null, 617, 3, 1, 270,1.0);
INSERT INTO room_t VALUES(null, 618, 3, 1, 270,1.0);
INSERT INTO room_t VALUES(null, 619, 3, 1, 270,1.0);
INSERT INTO room_t VALUES(null, 620, 3, 1, 270,1.0);

INSERT INTO room_t VALUES(null, 701, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 702, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 703, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 704, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 705, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 706, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 707, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 708, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 709, 1, 1, 240,1.0);
INSERT INTO room_t VALUES(null, 710, 1, 1, 240,1.0);

INSERT INTO room_t VALUES(null, 711, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 712, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 713, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 714, 2, 1, 220,1.0);
INSERT INTO room_t VALUES(null, 715, 2, 1, 220,1.0);

INSERT INTO room_t VALUES(null, 716, 4, 1, 360,1.0);
INSERT INTO room_t VALUES(null, 717, 4, 1, 360,1.0);
INSERT INTO room_t VALUES(null, 718, 4, 1, 360,1.0);
INSERT INTO room_t VALUES(null, 719, 4, 1, 360,1.0);
INSERT INTO room_t VALUES(null, 720, 4, 1, 360,1.0);


----------------------------------------
-- 创建评价信息表
----------------------------------------
CREATE TABLE evluate_t(
	eid		INTEGER PRIMARY KEY,	-- 评价ID号
	rank	INTEGER,				-- 评价级别，0：满意，1：一般，2：不满意
	content	TEXT					-- 评价的内容
);

--INSERT INTO evluate_t VALUES(50000, 0, "很好很强大，很爽很舒服");
--INSERT INTO evluate_t VALUES(null, 1, "前台太丑了，影响顾客心情");

----------------------------------------
-- 创建统计信息表
----------------------------------------
CREATE TABLE sum_t(
	sid		INTEGER PRIMARY KEY,	-- 收入ID号
	money			INTEGER,	-- 收入总数
	num_room		INTEGER,		-- 现在使用的房间数
	num_people		INTEGER		-- 现在入住的人数
);

INSERT INTO sum_t VALUES(100000, 0, 0, 0);

CREATE TABLE time_t(
	tid INTEGER PRIMARY KEY,    -- 时间标号
  thedate DATE,               -- 现在的日期
  thetime TIME                -- 现在的时间
);

INSERT INTO time_t VALUES(100010,date(),time());