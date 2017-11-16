use restaurantBooking;

/*
Data Set For Homework 3 Problem 1

Source Database       : restaurant booking
Target Server Type    : MYSQL
Date: 2017-03-21 12:12:34
*/

DROP TABLE IF EXISTS `booking`;
DROP TABLE IF EXISTS `restaurant`;
DROP TABLE IF EXISTS `customer`;

-- ----------------------------
-- Table structure for `customer`
-- ----------------------------

CREATE TABLE `customer` (
  `cid` INT NOT NULL,
  `cname` VARCHAR(45) NOT NULL,
  `phone` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`cid`));

-- ----------------------------
-- Records of customer
-- ----------------------------
INSERT INTO `customer` VALUES (1, 'Antonio Rod', '48596784756');
INSERT INTO `customer` VALUES (2, 'Jerry Huang', '8476372654');
INSERT INTO `customer` VALUES (3, 'Brown Snow', '34857694038');
INSERT INTO `customer` VALUES (4, 'Guru Singh', '3847596878');
INSERT INTO `customer` VALUES (5, 'Ivy Yu', '2039485768');
INSERT INTO `customer` VALUES (6, 'Jack Smith', '9178594837');
INSERT INTO `customer` VALUES (7, 'Jane Jing', '39485068594');
INSERT INTO `customer` VALUES (8, 'Tom White', '45783940587');

-- ----------------------------
-- Table structure for `restaurant`
-- ----------------------------
CREATE TABLE `restaurant` (
  `rid` INT NOT NULL,
  `rname` VARCHAR(45) NOT NULL,
  `raddress` VARCHAR(45) NOT NULL,
  `description` VARCHAR(200) NOT NULL,
  `capacity` INT NOT NULL,
  PRIMARY KEY (`rid`));

-- ----------------------------
-- Records of restaurant
-- ----------------------------
INSERT INTO `restaurant` VALUES (1, 'Teriyaki Chicken', '812 Grand St, Brooklyn, NY', 'Korean BBQ Chicken, Korean Fried Chicken ,Salad', 50);
INSERT INTO `restaurant` VALUES (2, 'Crab Club', '400 Jay Street, Brooklyn, NY', 'Crab, Lobster, Shrimp, Oyster', 30);
INSERT INTO `restaurant` VALUES (3, 'Peking Restaurant', '120 Willoughby Street, Brooklyn, NY', 'Traditional Chinese food', 50);
INSERT INTO `restaurant` VALUES (4, 'Indian Kitchen', '300 Bridge Street, Brooklyn, NY', 'Traditional Chinese food', 50);
INSERT INTO `restaurant` VALUES (5, 'Sushi Bar', '309 Gold Street, Brooklyn, NY', 'Sushi, Sashimi, Ramen', 20);

-- ----------------------------
-- Table structure for booking
-- ----------------------------

CREATE TABLE `booking` (
  `bid` INT NOT NULL AUTO_INCREMENT,
  `cid` INT NOT NULL,
  `rid` INT NOT NULL,
  `btime` DATETIME NOT NULL,
  `quantity` INT NOT NULL,
  PRIMARY KEY (`bid`),
  CONSTRAINT `customer_fk` FOREIGN KEY (`cid`) REFERENCES `customer` (`cid`),
  CONSTRAINT `restaurant_fk` FOREIGN KEY (`rid`) REFERENCES `restaurant` (`rid`));

-- ----------------------------
-- Records of booking
-- ----------------------------
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (1, 1, '2017-11-05 12:00:00', 10);
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (2, 3, '2017-11-06 11:00:00', 10);
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (3, 2, '2017-11-04 18:00:00', 5);
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (4, 1, '2017-11-05 12:00:00', 10);
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (5, 1, '2017-11-05 12:00:00', 10);
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (3, 4, '2017-11-08 19:00:00', 15);
INSERT INTO `booking` (cid, rid, btime, quantity) VALUES (2, 5, '2017-11-07 20:00:00', 10);
