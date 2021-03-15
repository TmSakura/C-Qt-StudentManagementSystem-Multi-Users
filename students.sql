-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- 主机： 127.0.0.1
-- 生成日期： 2021-03-15 06:54:52
-- 服务器版本： 10.4.17-MariaDB
-- PHP 版本： 8.0.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 数据库： `students`
--

-- --------------------------------------------------------

--
-- 表的结构 `blood`
--

CREATE TABLE `blood` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `blood`
--

INSERT INTO `blood` (`name`) VALUES
('AB型'),
('O型');

-- --------------------------------------------------------

--
-- 表的结构 `city`
--

CREATE TABLE `city` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `city`
--

INSERT INTO `city` (`name`) VALUES
('宁波市'),
('昆山市');

-- --------------------------------------------------------

--
-- 表的结构 `college`
--

CREATE TABLE `college` (
  `name` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `college`
--

INSERT INTO `college` (`name`) VALUES
('医学院'),
('经济学院'),
('数学科学学院'),
('物理学院'),
('工学院');

-- --------------------------------------------------------

--
-- 表的结构 `debt`
--

CREATE TABLE `debt` (
  `number` varchar(50) NOT NULL,
  `subject` varchar(50) NOT NULL,
  `grade` varchar(20) NOT NULL,
  `type` varchar(20) NOT NULL,
  `date` varchar(50) NOT NULL,
  `semester` varchar(20) NOT NULL,
  `year` varchar(20) NOT NULL,
  `time` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 表的结构 `eye`
--

CREATE TABLE `eye` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `eye`
--

INSERT INTO `eye` (`name`) VALUES
('褐色'),
('棕色');

-- --------------------------------------------------------

--
-- 表的结构 `file`
--

CREATE TABLE `file` (
  `number` varchar(50) DEFAULT NULL,
  `file1` varchar(100) DEFAULT NULL,
  `file2` varchar(100) DEFAULT NULL,
  `file3` varchar(100) DEFAULT NULL,
  `file4` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 表的结构 `grade`
--

CREATE TABLE `grade` (
  `number` varchar(20) NOT NULL,
  `subject` varchar(20) NOT NULL,
  `grade` varchar(20) NOT NULL,
  `date` varchar(20) DEFAULT NULL,
  `semester` varchar(20) NOT NULL,
  `year` varchar(20) NOT NULL,
  `time` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `grade`
--

INSERT INTO `grade` (`number`, `subject`, `grade`, `date`, `semester`, `year`, `time`) VALUES
('1616466001', '大学英语2', '234', '', '1', '2019', 'Mon Mar 15 11:20:36 2021');

-- --------------------------------------------------------

--
-- 表的结构 `honor`
--

CREATE TABLE `honor` (
  `number` varchar(50) NOT NULL,
  `name` varchar(50) NOT NULL,
  `level` varchar(50) NOT NULL,
  `date` varchar(50) NOT NULL,
  `semester` varchar(50) NOT NULL,
  `year` varchar(50) NOT NULL,
  `time` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 表的结构 `nation`
--

CREATE TABLE `nation` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `nation`
--

INSERT INTO `nation` (`name`) VALUES
('汉族'),
('维吾尔族'),
('彝族'),
('苗族'),
('蒙古族');

-- --------------------------------------------------------

--
-- 表的结构 `political`
--

CREATE TABLE `political` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `political`
--

INSERT INTO `political` (`name`) VALUES
('群众'),
('团员'),
('党员');

-- --------------------------------------------------------

--
-- 表的结构 `profession`
--

CREATE TABLE `profession` (
  `name` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `profession`
--

INSERT INTO `profession` (`name`) VALUES
('计算机科学与技术'),
('数学');

-- --------------------------------------------------------

--
-- 表的结构 `province`
--

CREATE TABLE `province` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `province`
--

INSERT INTO `province` (`name`) VALUES
(''),
('浙江省'),
('江苏省'),
('河北省'),
('山西省'),
('辽宁省'),
('河南省'),
('四川省'),
('湖北省'),
('安徽省'),
('海南省');

-- --------------------------------------------------------

--
-- 表的结构 `punish`
--

CREATE TABLE `punish` (
  `number` varchar(50) NOT NULL,
  `reason` varchar(50) NOT NULL,
  `handling` varchar(50) NOT NULL,
  `date` varchar(50) NOT NULL,
  `semester` varchar(50) NOT NULL,
  `year` varchar(50) NOT NULL,
  `result` varchar(50) NOT NULL,
  `time` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 表的结构 `scholarship`
--

CREATE TABLE `scholarship` (
  `number` varchar(50) NOT NULL,
  `count` varchar(20) NOT NULL,
  `date` varchar(20) NOT NULL,
  `semester` varchar(20) NOT NULL,
  `year` varchar(20) NOT NULL,
  `time` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 表的结构 `semester`
--

CREATE TABLE `semester` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `semester`
--

INSERT INTO `semester` (`name`) VALUES
('1'),
('2');

-- --------------------------------------------------------

--
-- 表的结构 `skin`
--

CREATE TABLE `skin` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `skin`
--

INSERT INTO `skin` (`name`) VALUES
('黄色'),
('白色');

-- --------------------------------------------------------

--
-- 表的结构 `socialstatus`
--

CREATE TABLE `socialstatus` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `socialstatus`
--

INSERT INTO `socialstatus` (`name`) VALUES
('微博'),
('QQ'),
('Facebook');

-- --------------------------------------------------------

--
-- 表的结构 `status`
--

CREATE TABLE `status` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `status`
--

INSERT INTO `status` (`name`) VALUES
('在校'),
('毕业'),
('隔离');

-- --------------------------------------------------------

--
-- 表的结构 `studentinfo`
--

CREATE TABLE `studentinfo` (
  `name` varchar(20) NOT NULL,
  `number` varchar(50) NOT NULL,
  `sex` varchar(10) NOT NULL,
  `nation` varchar(10) NOT NULL,
  `political` varchar(10) NOT NULL,
  `birthData` varchar(20) NOT NULL,
  `birthPlace` varchar(50) NOT NULL,
  `idCard` varchar(50) NOT NULL,
  `province` varchar(50) NOT NULL,
  `city` varchar(50) NOT NULL,
  `university` varchar(50) NOT NULL,
  `college` varchar(50) NOT NULL,
  `profession` varchar(50) NOT NULL,
  `status` varchar(10) NOT NULL,
  `dataOfAdmission` varchar(20) NOT NULL,
  `dataOfGraduation` varchar(20) NOT NULL,
  `homeAddress` varchar(50) NOT NULL,
  `phone` varchar(20) NOT NULL,
  `socialStatus` varchar(10) NOT NULL,
  `blood` varchar(10) NOT NULL,
  `eye` varchar(10) NOT NULL,
  `skin` varchar(10) NOT NULL,
  `fatherName` varchar(20) NOT NULL,
  `fatherWork` varchar(20) NOT NULL,
  `motherName` varchar(20) NOT NULL,
  `motherWork` varchar(20) NOT NULL,
  `parentOtherInformation` varchar(200) DEFAULT NULL,
  `photo` varchar(50) DEFAULT NULL,
  `otherInterest` varchar(200) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `studentinfo`
--

INSERT INTO `studentinfo` (`name`, `number`, `sex`, `nation`, `political`, `birthData`, `birthPlace`, `idCard`, `province`, `city`, `university`, `college`, `profession`, `status`, `dataOfAdmission`, `dataOfGraduation`, `homeAddress`, `phone`, `socialStatus`, `blood`, `eye`, `skin`, `fatherName`, `fatherWork`, `motherName`, `motherWork`, `parentOtherInformation`, `photo`, `otherInterest`) VALUES
('陈1', '1616466001', '男', '汉族', '群众', '4/12/1998', '江苏省苏州市昆山市', '320583199804122568', '浙江省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '毕业', '9/1/2016', '7/1/2020', '江苏省苏州市昆山市', '13913271901', 'QQ', 'AB型', '褐色', '黄色', '陈11', '为国家工作', '陈12', '自由职业者', '', '', '篮球'),
('陈2', '1616466002', '女', '汉族', '群众', '4/5/1997', '江苏省苏州市昆山市', '320583199704052565', '浙江省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '9/1/2016', '7/1/2020', '江苏省苏州市昆山市', '13913271902', 'QQ', 'AB型', '褐色', '黄色', '陈21', '为国家工作', '陈22', '自由职业者', '', '', '篮球'),
('陈3', '1616466003', '男', '汉族', '群众', '12/1/1997', '江苏省苏州市昆山市', '320583199804122568', '河北省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '1/9/2016', '1/7/2020', '江苏省苏州市昆山市', '13913271903', 'QQ', 'AB型', '褐色', '黄色', '陈31', '为国家工作', '陈32', '自由职业者', '', '', '篮球'),
('陈4', '1616466004', '男', '汉族', '群众', '1/1/2000', '江苏省苏州市昆山市', '320583199804122568', '安徽省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '1/9/2016', '1/7/2020', '江苏省苏州市昆山市', '13913271904', 'QQ', 'AB型', '褐色', '黄色', '陈41', '为国家工作', '陈42', '自由职业者', '', '', '篮球'),
('陈5', '1616466005', '男', '汉族', '群众', '2/7/1997', '江苏省苏州市昆山市', '320583199804122568', '江苏省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '9/1/2016', '7/1/2020', '江苏省苏州市昆山市', '13913271905', 'QQ', 'AB型', '褐色', '黄色', '陈51', '为国家工作', '陈52', '自由职业者', '', '', '篮球'),
('陈6', '1616466006', '男', '汉族', '群众', '6/6/1997', '江苏省苏州市昆山市', '320583199804122568', '安徽省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '1/9/2016', '1/7/2020', '江苏省苏州市昆山市', '13913271906', 'QQ', 'AB型', '褐色', '黄色', '陈61', '为国家工作', '陈62', '自由职业者', '', '', '篮球'),
('陈7', '1616466007', '男', '汉族', '群众', '5/5/1998', '江苏省苏州市昆山市', '320583199804122568', '湖北省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '1/9/2016', '1/7/2020', '江苏省苏州市昆山市', '13913271907', 'QQ', 'AB型', '褐色', '黄色', '陈72', '为国家工作', '陈72', '自由职业者', '', '', '篮球'),
('陈8', '1616466008', '男', '汉族', '群众', '2/9/1997', '江苏省苏州市昆山市', '320583199804122568', '浙江省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '1/9/2016', '1/7/2020', '江苏省苏州市昆山市', '13913271908', 'QQ', 'AB型', '褐色', '黄色', '陈81', '为国家工作', '陈82', '自由职业者', '', '', '篮球'),
('陈9', '1616466009', '男', '汉族', '群众', '7/7/1998', '江苏省苏州市昆山市', '320583199804122568', '江苏省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '9/1/2016', '7/1/2020', '江苏省苏州市昆山市', '13913271909', 'QQ', 'AB型', '褐色', '黄色', '陈91', '为国家工作', '陈92', '自由职业者', '', '', '篮球'),
('陈10', '1616466010', '男', '汉族', '群众', '5/2/1997', '江苏省苏州市昆山市', '320583199804122568', '江苏省', '昆山市', '苏州大学', '工学院', '计算机科学与技术', '在校', '9/1/2016', '7/1/2020', '江苏省苏州市昆山市', '13913271910', 'QQ', 'AB型', '褐色', '黄色', '陈101', '为国家工作', '陈02', '自由职业者', '', '', '篮球');

-- --------------------------------------------------------

--
-- 表的结构 `subject`
--

CREATE TABLE `subject` (
  `name` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `subject`
--

INSERT INTO `subject` (`name`) VALUES
('大学英语1'),
('大学英语2'),
('离散数学'),
('大学英语3'),
('大学英语4');

-- --------------------------------------------------------

--
-- 表的结构 `typeofexam`
--

CREATE TABLE `typeofexam` (
  `name` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `typeofexam`
--

INSERT INTO `typeofexam` (`name`) VALUES
('通识教育课程'),
('专业必修课程');

-- --------------------------------------------------------

--
-- 表的结构 `university`
--

CREATE TABLE `university` (
  `name` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `university`
--

INSERT INTO `university` (`name`) VALUES
('苏州大学应用技术学院'),
('苏州大学'),
('苏州科技大学'),
('苏州大学文正学院');

-- --------------------------------------------------------

--
-- 表的结构 `user`
--

CREATE TABLE `user` (
  `username` varchar(100) NOT NULL,
  `password` varchar(100) NOT NULL,
  `read` varchar(10) NOT NULL,
  `write` varchar(10) NOT NULL,
  `remove` varchar(10) NOT NULL,
  `search` varchar(10) NOT NULL,
  `print` varchar(10) NOT NULL,
  `import` varchar(10) NOT NULL,
  `admin` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `user`
--

INSERT INTO `user` (`username`, `password`, `read`, `write`, `remove`, `search`, `print`, `import`, `admin`) VALUES
('admin', '123456', 'Yes', 'Yes', 'Yes', 'Yes', 'Yes', 'Yes', 'Yes');

-- --------------------------------------------------------

--
-- 表的结构 `year`
--

CREATE TABLE `year` (
  `name` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- 转存表中的数据 `year`
--

INSERT INTO `year` (`name`) VALUES
('2019'),
('2018'),
('2017'),
('2020');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
