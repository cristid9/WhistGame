-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: WhistGame
-- ------------------------------------------------------
-- Server version	5.5.41-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `blacklist`
--

DROP TABLE IF EXISTS `blacklist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `blacklist` (
  `userId` bigint(20) unsigned DEFAULT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `period` tinyint(3) unsigned DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `blacklist`
--

LOCK TABLES `blacklist` WRITE;
/*!40000 ALTER TABLE `blacklist` DISABLE KEYS */;
/*!40000 ALTER TABLE `blacklist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `friendRequests`
--

DROP TABLE IF EXISTS `friendRequests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `friendRequests` (
  `senderId` bigint(20) unsigned DEFAULT NULL,
  `receiverId` bigint(20) unsigned DEFAULT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `friendRequests`
--

LOCK TABLES `friendRequests` WRITE;
/*!40000 ALTER TABLE `friendRequests` DISABLE KEYS */;
/*!40000 ALTER TABLE `friendRequests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `friends`
--

DROP TABLE IF EXISTS `friends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `friends` (
  `userId` bigint(20) unsigned DEFAULT NULL,
  `friendId` bigint(20) unsigned DEFAULT NULL,
  `dateGiftFriend` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `dateGiftUser` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `friends`
--

LOCK TABLES `friends` WRITE;
/*!40000 ALTER TABLE `friends` DISABLE KEYS */;
INSERT INTO `friends` VALUES (1,2,'0000-00-00 00:00:00','0000-00-00 00:00:00'),(4,1,'0000-00-00 00:00:00','0000-00-00 00:00:00'),(2,4,'0000-00-00 00:00:00','0000-00-00 00:00:00'),(4,3,'0000-00-00 00:00:00','0000-00-00 00:00:00');
/*!40000 ALTER TABLE `friends` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `levels`
--

DROP TABLE IF EXISTS `levels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `levels` (
  `levels` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `exp` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`levels`)
) ENGINE=InnoDB AUTO_INCREMENT=101 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `levels`
--

LOCK TABLES `levels` WRITE;
/*!40000 ALTER TABLE `levels` DISABLE KEYS */;
INSERT INTO `levels` VALUES (1,100),(2,110),(3,121),(4,133),(5,146),(6,160),(7,176),(8,193),(9,212),(10,233),(11,256),(12,281),(13,309),(14,339),(15,372),(16,409),(17,449),(18,493),(19,542),(20,596),(21,655),(22,720),(23,792),(24,871),(25,958),(26,1053),(27,1158),(28,1273),(29,1400),(30,1540),(31,1694),(32,1863),(33,2049),(34,2253),(35,2478),(36,2725),(37,2997),(38,3296),(39,3625),(40,3987),(41,4385),(42,4823),(43,5305),(44,5835),(45,6418),(46,7059),(47,7764),(48,8540),(49,9394),(50,10333),(51,11366),(52,12502),(53,13752),(54,15127),(55,16639),(56,18302),(57,20132),(58,22145),(59,24359),(60,26794),(61,29473),(62,32420),(63,35662),(64,39228),(65,43150),(66,47465),(67,52211),(68,57432),(69,63175),(70,69492),(71,76441),(72,84085),(73,92493),(74,101742),(75,111916),(76,123107),(77,135417),(78,148958),(79,163853),(80,180238),(81,198261),(82,218087),(83,239895),(84,263884),(85,290272),(86,319299),(87,351228),(88,386350),(89,424985),(90,467483),(91,514231),(92,565654),(93,622219),(94,684440),(95,752884),(96,828172),(97,910989),(98,1002087),(99,1102295),(100,1212524);
/*!40000 ALTER TABLE `levels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `notifications`
--

DROP TABLE IF EXISTS `notifications`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `notifications` (
  `userId` bigint(20) unsigned DEFAULT NULL,
  `content` varchar(100) DEFAULT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `seen` tinyint(1) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `notifications`
--

LOCK TABLES `notifications` WRITE;
/*!40000 ALTER TABLE `notifications` DISABLE KEYS */;
INSERT INTO `notifications` VALUES (2,'admin1 sent you friend request.','2015-03-18 18:24:58',0),(1,'You have sent friend request to admin2.','2015-03-18 18:24:58',0),(3,'admin1 sent you friend request.','2015-03-18 18:24:59',0),(1,'You have sent friend request to admin3.','2015-03-18 18:24:59',0),(1,'admin4 sent you friend request.','2015-03-18 18:24:59',0),(4,'You have sent friend request to admin1.','2015-03-18 18:24:59',0),(1,'admin5 sent you friend request.','2015-03-18 18:24:59',0),(5,'You have sent friend request to admin1.','2015-03-18 18:24:59',0),(4,'admin2 sent you friend request.','2015-03-18 18:24:59',0),(2,'You have sent friend request to admin4.','2015-03-18 18:24:59',0),(3,'admin4 sent you friend request.','2015-03-18 18:24:59',0),(4,'You have sent friend request to admin3.','2015-03-18 18:24:59',0),(8,'admin2 sent you friend request.','2015-03-18 18:24:59',0),(2,'You have sent friend request to admin8.','2015-03-18 18:24:59',0),(1,'admin2 accepted your friend request.','2015-03-18 18:24:59',0),(2,'You became friend with admin1.','2015-03-18 18:24:59',0),(4,'admin1 accepted your friend request.','2015-03-18 18:25:00',0),(1,'You became friend with admin4.','2015-03-18 18:25:00',0),(2,'admin4 accepted your friend request.','2015-03-18 18:25:00',0),(4,'You became friend with admin2.','2015-03-18 18:25:00',0),(4,'admin3 accepted your friend request.','2015-03-18 18:25:00',0),(3,'You became friend with admin4.','2015-03-18 18:25:00',0),(2,'admin8 accepted your friend request.','2015-03-18 18:25:00',0),(8,'You became friend with admin2.','2015-03-18 18:25:00',0),(1,'admin3 refused your friend request.','2015-03-18 18:25:00',0),(3,'You have refused the friend request sent of admin1.','2015-03-18 18:25:00',0),(5,'admin1 refused your friend request.','2015-03-18 18:25:00',0),(1,'You have refused the friend request sent of admin5.','2015-03-18 18:25:00',0),(2,'admin8 removed you from friends.','2015-03-18 18:25:00',0),(8,'You have removed from friends on admin2','2015-03-18 18:25:00',0);
/*!40000 ALTER TABLE `notifications` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `players` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(30) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `password` varchar(35) DEFAULT NULL,
  `points` bigint(20) unsigned DEFAULT '3000',
  `games` bigint(20) unsigned DEFAULT '0',
  `wonGames` bigint(20) unsigned DEFAULT '0',
  `registerDate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `loginDate` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `day` tinyint(4) DEFAULT '0',
  `activated` tinyint(1) DEFAULT '0',
  `avatarName` varchar(15) DEFAULT 'default.png',
  `rank` tinyint(4) DEFAULT '1',
  `userLevel` tinyint(3) unsigned DEFAULT '1',
  `currentExp` bigint(20) unsigned DEFAULT '0',
  `blockedPrivMessages` tinyint(3) unsigned DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `players`
--

LOCK TABLES `players` WRITE;
/*!40000 ALTER TABLE `players` DISABLE KEYS */;
INSERT INTO `players` VALUES (1,'admin1','admin1@gmail.com','e00cf25ad42683b3df678c61f42c6bda',5800,7,5,'2015-03-14 10:11:46','2015-04-11 11:58:07',1,1,'default.png',5,5,136,0),(2,'admin2','admin2@gmail.com','c84258e9c39059a89ab77d846ddab909',4800,0,0,'2015-03-14 10:12:29','2015-04-11 11:01:59',1,1,'default.png',4,1,0,0),(3,'admin3','admin3@gmail.com','32cacb2f994f6b42183a1300d9a3e8d6',3200,0,0,'2015-03-14 17:58:39','2015-03-18 23:57:31',1,1,'default.png',3,1,0,0),(4,'admin4','admin4@gmail.com','fc1ebc848e31e0a68e868432225e3c82',3200,0,0,'2015-03-14 17:58:56','2015-03-18 23:57:31',1,1,'default.png',2,1,0,0),(5,'admin5','admin5@gmail.com','26a91342190d515231d7238b0c5438e1',3200,0,0,'2015-03-14 17:59:00','2015-03-18 23:49:56',0,1,'default.png',1,1,0,0),(6,'admin6','admin6@gmail.com','c6b853d6a7cc7ec49172937f68f446c8',3150,0,0,'2015-03-14 17:59:04','2015-03-16 20:05:12',2,1,'default.png',1,1,0,0),(7,'admin7','admin7@gmail.com','788073cefde4b240873e1f52f5371d7d',3150,0,0,'2015-03-14 17:59:08','2015-03-16 20:05:12',2,1,'default.png',1,1,0,0),(8,'admin8','admin8@gmail.com','8762eb814817cc8dcbb3fb5c5fcd52e0',3050,0,0,'2015-03-14 23:14:16','2015-03-18 18:13:16',1,1,'default.png',1,1,0,0),(9,'admin9','admin9@gmail.com','eed57216df3731106517ccaf5da2122d',3050,0,0,'2015-03-14 23:14:16','2015-03-18 18:13:16',1,1,'default.png',1,1,0,0),(10,'admin10','admin10@gmail.com','4fbd41a36dac3cd79aa1041c9648ab89',3150,0,0,'2015-03-15 08:41:09','2015-03-18 23:58:41',1,1,'default.png',1,1,0,0);
/*!40000 ALTER TABLE `players` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-04-16 12:00:01
