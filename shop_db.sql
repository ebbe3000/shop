-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Cze 12, 2024 at 11:37 AM
-- Wersja serwera: 10.4.32-MariaDB
-- Wersja PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `shop_db`
--

DELIMITER $$
--
-- Procedury
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `editUserData` (IN `in_id` INT(8), IN `in_name` VARCHAR(30), IN `in_surname` VARCHAR(50), IN `in_email` VARCHAR(50), IN `in_passwd` VARCHAR(50), IN `in_province` VARCHAR(30), IN `in_p_code` VARCHAR(6), IN `in_city` VARCHAR(50), IN `in_address` VARCHAR(50))   BEGIN

set @id = 0;

SELECT id_p INTO @id
FROM provinces p 
WHERE p.name = in_province;

UPDATE users
SET first_name = in_name, surname = in_surname, email = in_email, passwd = in_passwd, id_prov = @id, p_code = in_p_code, city = in_city, address = in_address 
WHERE id_u = in_id;

END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `insertUser` (IN `in_name` VARCHAR(30), IN `in_surname` VARCHAR(50), IN `in_email` VARCHAR(50), IN `in_passwd` VARCHAR(50), IN `in_province` VARCHAR(30), IN `in_p_code` VARCHAR(6), IN `in_city` VARCHAR(50), IN `in_address` VARCHAR(50))   BEGIN

set @id = 0;

SELECT id_p INTO @id
FROM provinces p 
WHERE p.name = in_province;

INSERT INTO users(first_name, surname, email, passwd, id_prov, p_code, city, address)
VALUES (in_name, in_surname, in_email, in_passwd, @id, in_p_code, in_city, in_address);

END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `users_balance` ()   BEGIN

CREATE TEMPORARY TABLE profits(id_u INT(8) PRIMARY KEY, val FLOAT(8, 2));

INSERT INTO profits(id_u, val) 
SELECT p.id_u, SUM(pp.amount * p.price) 
FROM purchased_products pp 
INNER JOIN products p ON pp.id_p = p.id_p 
GROUP BY p.id_u 
ORDER BY p.id_u ASC;


CREATE TEMPORARY TABLE expenses(id_u INT(8) PRIMARY KEY, val FLOAT(8, 2));

INSERT INTO expenses(id_u, val)
	SELECT pp.id_u, SUM(pp.amount * p.price) AS payed
	FROM purchased_products pp
	INNER JOIN products p ON pp.id_p = p.id_p
	GROUP BY pp.id_u
	ORDER BY pp.id_u ASC;
    
    
SELECT u.id_u, IFNULL(p.val, 0) - IFNULL(e.val, 0) AS account_ballance
FROM users u
LEFT JOIN profits p ON u.id_u = p.id_u
LEFT JOIN expenses e ON u.id_u = e.id_u
GROUP BY u.id_u
ORDER BY u.id_u ASC;

DROP TEMPORARY TABLE profits;
DROP TEMPORARY TABLE expenses;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `categories`
--

CREATE TABLE `categories` (
  `id_c` int(8) NOT NULL,
  `cat_name` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `categories`
--

INSERT INTO `categories` (`id_c`, `cat_name`) VALUES
(1, 'Elektronika'),
(2, 'Moda'),
(3, 'Dom i ogród'),
(4, 'Uroda'),
(5, 'Sport'),
(6, 'Motoryzacja'),
(7, 'Supermarket'),
(8, 'Zdrowie'),
(9, 'Sztuka');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `categorized_products`
--

CREATE TABLE `categorized_products` (
  `id_p` int(8) NOT NULL,
  `id_c` int(8) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `categorized_products`
--

INSERT INTO `categorized_products` (`id_p`, `id_c`) VALUES
(26, 2),
(26, 5),
(27, 5),
(28, 1),
(29, 6),
(30, 4),
(30, 8),
(36, 5),
(36, 9),
(37, 1),
(37, 5),
(37, 7),
(38, 1),
(38, 2),
(38, 7),
(39, 2),
(39, 3),
(39, 5),
(40, 1),
(40, 2),
(40, 5),
(41, 1),
(41, 2),
(41, 5),
(42, 1),
(42, 2),
(42, 5),
(43, 1),
(43, 2),
(43, 5);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `loggs`
--

CREATE TABLE `loggs` (
  `id` int(8) NOT NULL,
  `date_time` datetime DEFAULT NULL,
  `operation` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `loggs`
--

INSERT INTO `loggs` (`id`, `date_time`, `operation`) VALUES
(1, NULL, 'Próba dodania nowego uzytkowni'),
(2, NULL, 'Dodano nowego uzytkownika: id_'),
(3, NULL, 'Próba dodania nowego uzytkowni'),
(4, NULL, 'Dodano nowego uzytkownika: id_'),
(5, NULL, 'Próba dodania nowego uzytkowni'),
(6, NULL, 'Dodano nowego uzytkownika: id_'),
(7, NULL, 'Próba dodania nowego uzytkowni'),
(8, NULL, 'Dodano nowego uzytkownika: id_'),
(9, NULL, 'Próba dodania nowego uzytkowni'),
(10, NULL, 'Dodano nowego uzytkownika: id_'),
(11, NULL, 'Próba dodania nowego uzytkowni'),
(12, NULL, 'Dodano nowego uzytkownika: id_'),
(13, NULL, 'Próba dodania nowego uzytkowni'),
(14, NULL, 'Dodano nowego uzytkownika: id_'),
(15, NULL, 'Próba dodania nowego uzytkowni'),
(16, NULL, 'Dodano nowego uzytkownika: id_'),
(17, NULL, 'Próba dodania nowego produktu:'),
(18, NULL, 'Dodano nowy produkt: id=26, id'),
(19, NULL, 'Próba dodania nowego produktu:'),
(20, NULL, 'Dodano nowy produkt: id=27, id'),
(21, NULL, 'Próba dodania nowego produktu:'),
(22, NULL, 'Dodano nowy produkt: id=28, id'),
(23, NULL, 'Próba dodania nowego produktu:'),
(24, NULL, 'Dodano nowy produkt: id=29, id'),
(25, NULL, 'Próba dodania nowego produktu:'),
(26, NULL, 'Dodano nowy produkt: id=30, id'),
(27, NULL, 'Próba dodania nowego produktu:'),
(28, NULL, 'Dodano nowy produkt: id=31, id'),
(29, NULL, 'Próba dodania nowego produktu:'),
(30, NULL, 'Dodano nowy produkt: id=32, id'),
(31, NULL, 'Próba dodania nowego produktu:'),
(32, NULL, 'Dodano nowy produkt: id=33, id'),
(33, NULL, 'Próba dodania nowego produktu:'),
(34, NULL, 'Dodano nowy produkt: id=34, id'),
(35, NULL, 'Próba dodania nowego produktu:'),
(36, NULL, 'Dodano nowy produkt: id=35, id'),
(37, NULL, 'Próba dodania nowego uzytkowni'),
(38, NULL, 'Dodano nowego uzytkownika: id_'),
(39, NULL, 'Próba dodania nowego produktu:'),
(40, NULL, 'Dodano nowy produkt: id=36, id'),
(41, NULL, 'Próba dodania nowego produktu:'),
(42, NULL, 'Dodano nowy produkt: id=37, id'),
(43, NULL, 'Próba dodania nowego uzytkowni'),
(44, NULL, 'Dodano nowego uzytkownika: id_'),
(45, NULL, 'Próba dodania nowego produktu:'),
(46, NULL, 'Dodano nowy produkt: id=38, id'),
(47, NULL, 'Próba dodania nowego produktu:'),
(48, NULL, 'Dodano nowy produkt: id=39, id'),
(49, NULL, 'Próba dodania nowego produktu:'),
(50, NULL, 'Dodano nowy produkt: id=40, id'),
(51, NULL, 'Próba dodania nowego produktu:'),
(52, NULL, 'Dodano nowy produkt: id=41, id'),
(53, NULL, 'Próba dodania nowego produktu:'),
(54, NULL, 'Dodano nowy produkt: id=42, id'),
(55, NULL, 'Próba dodania nowego produktu:'),
(56, NULL, 'Dodano nowy produkt: id=43, id'),
(57, NULL, 'Próba dodania nowego produktu:'),
(58, NULL, 'Dodano nowy produkt: id=44, id'),
(59, NULL, 'Próba dodania nowego produktu:'),
(60, NULL, 'Dodano nowy produkt: id=45, id'),
(61, NULL, 'Próba dodania nowego produktu:'),
(62, NULL, 'Dodano nowy produkt: id=46, id'),
(63, NULL, 'Próba dodania nowego produktu:'),
(64, NULL, 'Dodano nowy produkt: id=47, id'),
(65, NULL, 'Próba dodania nowego produktu:'),
(66, NULL, 'Dodano nowy produkt: id=48, id'),
(67, NULL, 'Próba dodania nowego produktu:'),
(68, NULL, 'Dodano nowy produkt: id=49, id'),
(69, NULL, 'Próba dodania nowego produktu:'),
(70, NULL, 'Dodano nowy produkt: id=50, id'),
(71, NULL, 'Próba dodania nowego produktu:'),
(72, NULL, 'Dodano nowy produkt: id=51, id'),
(73, NULL, 'Próba dodania nowego produktu:'),
(74, NULL, 'Dodano nowy produkt: id=52, id'),
(75, NULL, 'Próba dodania nowego produktu:'),
(76, NULL, 'Dodano nowy produkt: id=53, id'),
(77, NULL, 'Próba dodania nowego produktu:'),
(78, NULL, 'Dodano nowy produkt: id=54, id'),
(79, NULL, 'Próba dodania nowego produktu:'),
(80, NULL, 'Dodano nowy produkt: id=55, id'),
(81, NULL, 'Próba dodania nowego produktu:'),
(82, NULL, 'Dodano nowy produkt: id=56, id'),
(83, NULL, 'Próba dodania nowego produktu:'),
(84, NULL, 'Dodano nowy produkt: id=57, id'),
(85, NULL, 'Próba dodania nowego produktu:'),
(86, NULL, 'Dodano nowy produkt: id=58, id');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `path_to_images`
--

CREATE TABLE `path_to_images` (
  `id_p` int(8) DEFAULT NULL,
  `path` varchar(50) DEFAULT 'D:/shop/shop/imgs/q_mark.png'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `path_to_images`
--

INSERT INTO `path_to_images` (`id_p`, `path`) VALUES
(26, 'D:/shop/shop/imgs/FRrjGp.png'),
(26, 'D:/shop/shop/imgs/FxBTAh.png'),
(26, 'D:/shop/shop/imgs/oRixVd.png'),
(27, 'D:/shop/shop/imgs/RbYCIx.png'),
(28, 'D:/shop/shop/imgs/ZKUdak.png'),
(29, 'D:/shop/shop/imgs/vVdPjB.png'),
(30, 'D:/shop/shop/imgs/dwIpLs.png'),
(36, 'D:/shop/shop/imgs/EcriJZ.png'),
(36, 'D:/shop/shop/imgs/TTMrVo.png'),
(37, 'D:/shop/shop/imgs/ifumxp.png'),
(37, 'D:/shop/shop/imgs/Nfcsds.png'),
(38, 'D:/shop/shop/imgs/yDPGxG.png'),
(38, 'D:/shop/shop/imgs/LvKKiB.png'),
(39, 'D:/shop/shop/imgs/UaaZpK.png'),
(39, 'D:/shop/shop/imgs/cfLVXu.png'),
(40, 'D:/shop/shop/imgs/FeIZFM.png'),
(40, 'D:/shop/shop/imgs/JABNVO.png'),
(41, 'D:/shop/shop/imgs/SYOvYB.png'),
(42, 'D:/shop/shop/imgs/eYroLU.png'),
(43, 'D:/shop/shop/imgs/zJLLYw.png'),
(43, 'D:/shop/shop/imgs/sHMKSC.png');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `products`
--

CREATE TABLE `products` (
  `id_p` int(8) NOT NULL,
  `id_u` int(8) NOT NULL,
  `name` varchar(50) NOT NULL,
  `price` float(8,2) NOT NULL,
  `amount` int(5) DEFAULT NULL,
  `add_date` date NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  `active` tinyint(1) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `products`
--

INSERT INTO `products` (`id_p`, `id_u`, `name`, `price`, `amount`, `add_date`, `description`, `active`) VALUES
(26, 14, 'Buty', 249.99, 1, '2024-06-01', 'Nowe buty markowe.', 0),
(27, 14, 'Piłka do siatkówki', 150.00, 1, '2024-06-01', 'Nowe piłki Dippsta', 0),
(28, 17, 'Monitor 24\'', 449.99, 0, '2024-06-01', 'Monitory 60 Hz', 0),
(29, 17, 'Komplet opon zimowych', 1200.00, 0, '2024-06-01', 'Opony na zime dobrej firmy', 0),
(30, 19, 'Krem na noc', 34.99, 1, '2024-06-01', 'Krem na noc. Bardzo dobry.', 1),
(36, 25, 'Piłka Tango 2012', 33.33, 2, '2024-06-02', 'Piłka Jakuba Błaszczykowskiego', 0),
(37, 14, 'hehexd', 12.22, 5, '2024-06-08', 'opis', 0),
(38, 14, 'Produkt', 12.22, 22, '2024-06-09', '222OPisd', 0),
(39, 14, 'Produkt', 12.22, 2, '2024-06-09', 'Opisek', 0),
(40, 14, 'abcdef', 666.55, 2, '2024-06-09', 'hhahahax', 0),
(41, 14, 'nowy produkt', 12.22, 3, '2024-06-09', '75ufdsjn', 0),
(42, 14, 'nwoypr', 33.11, 3, '2024-06-09', 'ghfbdiogd', 0),
(43, 14, 'nowfsdfghnvu', 777.77, 1, '2024-06-09', 'abcedef', 1),
(44, 14, 'Product A', 19.99, 100, '2024-06-01', 'Description for Product A', 1),
(45, 15, 'Product B', 29.99, 150, '2024-06-02', 'Description for Product B', 1),
(46, 17, 'Product C', 39.99, 200, '2024-06-03', 'Description for Product C', 1),
(47, 18, 'Product D', 49.99, 250, '2024-06-04', 'Description for Product D', 1),
(48, 19, 'Product E', 59.99, 300, '2024-06-05', 'Description for Product E', 1),
(49, 25, 'Product F', 69.99, 350, '2024-06-06', 'Description for Product F', 1),
(50, 26, 'Product G', 79.99, 400, '2024-06-07', 'Description for Product G', 1),
(51, 14, 'Product H', 89.99, 450, '2024-06-08', 'Description for Product H', 1),
(52, 15, 'Product I', 99.99, 500, '2024-06-09', 'Description for Product I', 1),
(53, 17, 'Product J', 109.99, 550, '2024-06-10', 'Description for Product J', 1),
(54, 18, 'Product K', 119.99, 600, '2024-06-11', 'Description for Product K', 1),
(55, 19, 'Product L', 129.99, 650, '2024-06-12', 'Description for Product L', 1),
(56, 25, 'Product M', 139.99, 700, '2024-06-13', 'Description for Product M', 1),
(57, 26, 'Product N', 149.99, 750, '2024-06-14', 'Description for Product N', 1),
(58, 14, 'Product O', 159.99, 800, '2024-06-15', 'Description for Product O', 1);

--
-- Wyzwalacze `products`
--
DELIMITER $$
CREATE TRIGGER `after_product_insert` AFTER INSERT ON `products` FOR EACH ROW INSERT INTO loggs(operation)
VALUES (CONCAT('Dodano nowy produkt: id=', NEW.id_p, ', id_u=', NEW.id_u, ', name=', NEW.name, ', price=', NEW.price))
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `before_product_insert` BEFORE INSERT ON `products` FOR EACH ROW INSERT INTO loggs (operation)
VALUES (CONCAT('Próba dodania nowego produktu: name=', NEW.name, ', price=', NEW.price, ', amount=', NEW.amount))
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `provinces`
--

CREATE TABLE `provinces` (
  `id_p` int(8) NOT NULL,
  `name` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `provinces`
--

INSERT INTO `provinces` (`id_p`, `name`) VALUES
(1, 'Dolnośląskie'),
(2, 'Kujawsko-pomorskie'),
(3, 'Lubelskie'),
(4, 'Lubuskie'),
(5, 'Łódzkie'),
(6, 'Małopolskie'),
(7, 'Mazowieckie'),
(8, 'Opolskie'),
(9, 'Podkarpackie'),
(10, 'Podlaskie'),
(11, 'Pomorskie'),
(12, 'Śląskie'),
(13, 'Świętokrzyskie'),
(14, 'Warmińsko-mazurskie'),
(15, 'Wielkopolskie'),
(16, 'Zachodniopomorskie');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `purchased_products`
--

CREATE TABLE `purchased_products` (
  `id_u` int(8) NOT NULL,
  `id_p` int(8) NOT NULL,
  `amount` int(8) NOT NULL,
  `delivery_option` varchar(30) NOT NULL,
  `buyers_address` varchar(50) NOT NULL,
  `buy_time` datetime DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `purchased_products`
--

INSERT INTO `purchased_products` (`id_u`, `id_p`, `amount`, `delivery_option`, `buyers_address`, `buy_time`) VALUES
(15, 28, 1, 'Dostawa LHD', 'Poznań Krakowska 5', '2024-06-01 12:02:53'),
(15, 29, 1, 'Dostawa LHD', 'Poznań Krakowska 5', '2024-06-01 12:03:49'),
(17, 30, 2, 'Odbiór osobisty na UKSW', 'Nasielsk Leśna 13', '2024-06-01 12:24:15'),
(14, 28, 1, 'Dostawa LHD', 'Warszawa Wóycickiego', '2024-06-09 00:31:37');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `shopping_carts`
--

CREATE TABLE `shopping_carts` (
  `id_u` int(8) NOT NULL,
  `id_p` int(8) NOT NULL,
  `amount` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `shopping_carts`
--

INSERT INTO `shopping_carts` (`id_u`, `id_p`, `amount`) VALUES
(18, 27, 2);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `users`
--

CREATE TABLE `users` (
  `id_u` int(8) NOT NULL,
  `first_name` varchar(30) DEFAULT NULL,
  `surname` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `passwd` varchar(50) NOT NULL,
  `id_prov` int(8) DEFAULT NULL,
  `p_code` varchar(6) NOT NULL,
  `city` varchar(50) NOT NULL,
  `address` varchar(50) NOT NULL,
  `active` tinyint(1) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id_u`, `first_name`, `surname`, `email`, `passwd`, `id_prov`, `p_code`, `city`, `address`, `active`) VALUES
(14, 'Adam', 'Nowak', 'nowa@nowa', '123123', 16, '12-120', 'Warszawa', 'Wóycickiego', 1),
(15, 'Andrzej', 'Kowalski', 'kowal@kowal', '123321', 14, '00-000', 'Poznań', 'Krakowska 5', 1),
(17, 'Julianna', 'Bobko', 'bob@gmail.com', '111222', 7, '05-190', 'Nasielsk', 'Leśna 13', 1),
(18, 'Mirosław', 'Kuźnicki', 'miro@onet.pl', '321321', 16, '12-122', 'Płock', 'Basenowa 22', 1),
(19, 'Zuzanna', 'Pietryk', 'zupie@wp.pl', '123123123', 5, '15-190', 'Chrząszczyrzewoszyce', 'Duża 5', 1),
(25, 'Maciej', 'Grzywacki', 'grzywa@gmail.com', '123321123', 9, '12-303', 'Warszawa', 'Dworzec Gdański 15', 1),
(26, 'Krzysztof', 'Niegit', 'kubam@gmail.com', '123456', 7, '12-222', 'Warszawa', 'Wrocław', 1);

--
-- Wyzwalacze `users`
--
DELIMITER $$
CREATE TRIGGER `after_user_insert` AFTER INSERT ON `users` FOR EACH ROW INSERT INTO loggs(operation)
VALUES (CONCAT('Dodano nowego uzytkownika: id_u=', NEW.id_u, ', name=', NEW.first_name, ', surname=', NEW.surname))
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `before_user_insert` BEFORE INSERT ON `users` FOR EACH ROW INSERT INTO loggs(operation) 
VALUES (CONCAT('Próba dodania nowego uzytkownika: name=', NEW.first_name, ', surname=', NEW.surname))
$$
DELIMITER ;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`id_c`);

--
-- Indeksy dla tabeli `categorized_products`
--
ALTER TABLE `categorized_products`
  ADD KEY `FK_CATEGORIZED_PRODUCT_PRODUCTS` (`id_p`),
  ADD KEY `FK_CATEGORIZED_PRODUCT_CATEGORIES` (`id_c`);

--
-- Indeksy dla tabeli `loggs`
--
ALTER TABLE `loggs`
  ADD PRIMARY KEY (`id`);

--
-- Indeksy dla tabeli `path_to_images`
--
ALTER TABLE `path_to_images`
  ADD KEY `FK_PATH_TO_IMAGES_PRODUCTS` (`id_p`);

--
-- Indeksy dla tabeli `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id_p`),
  ADD KEY `FK_PRODUCTS_USERS` (`id_u`),
  ADD KEY `idx_product_name` (`name`),
  ADD KEY `idx_product_add_date` (`add_date`);

--
-- Indeksy dla tabeli `provinces`
--
ALTER TABLE `provinces`
  ADD PRIMARY KEY (`id_p`);

--
-- Indeksy dla tabeli `purchased_products`
--
ALTER TABLE `purchased_products`
  ADD KEY `FK_PURCHASED_PRODCUTS_PRODUCTS` (`id_p`),
  ADD KEY `FK_PURCHASED_PRODCUTS_USERS` (`id_u`);

--
-- Indeksy dla tabeli `shopping_carts`
--
ALTER TABLE `shopping_carts`
  ADD KEY `FK_SHOPPING_CART_USERS` (`id_u`),
  ADD KEY `FK_SHOPPING_CART_PRODUCTS` (`id_p`),
  ADD KEY `idx_shopping_cart_amount` (`amount`);

--
-- Indeksy dla tabeli `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id_u`),
  ADD KEY `FK_USERS_PROVINCES` (`id_prov`),
  ADD KEY `idx_fullname` (`surname`,`first_name`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `categories`
--
ALTER TABLE `categories`
  MODIFY `id_c` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `loggs`
--
ALTER TABLE `loggs`
  MODIFY `id` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=87;

--
-- AUTO_INCREMENT for table `products`
--
ALTER TABLE `products`
  MODIFY `id_p` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=59;

--
-- AUTO_INCREMENT for table `provinces`
--
ALTER TABLE `provinces`
  MODIFY `id_p` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id_u` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `categorized_products`
--
ALTER TABLE `categorized_products`
  ADD CONSTRAINT `FK_CATEGORIZED_PRODUCT_CATEGORIES` FOREIGN KEY (`id_c`) REFERENCES `categories` (`id_c`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_CATEGORIZED_PRODUCT_PRODUCTS` FOREIGN KEY (`id_p`) REFERENCES `products` (`id_p`) ON DELETE CASCADE;

--
-- Constraints for table `path_to_images`
--
ALTER TABLE `path_to_images`
  ADD CONSTRAINT `FK_PATH_TO_IMAGES_PRODUCTS` FOREIGN KEY (`id_p`) REFERENCES `products` (`id_p`) ON DELETE CASCADE;

--
-- Constraints for table `products`
--
ALTER TABLE `products`
  ADD CONSTRAINT `FK_PRODUCTS_USERS` FOREIGN KEY (`id_u`) REFERENCES `users` (`id_u`) ON DELETE CASCADE;

--
-- Constraints for table `purchased_products`
--
ALTER TABLE `purchased_products`
  ADD CONSTRAINT `FK_PURCHASED_PRODCUTS_PRODUCTS` FOREIGN KEY (`id_p`) REFERENCES `products` (`id_p`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_PURCHASED_PRODCUTS_USERS` FOREIGN KEY (`id_u`) REFERENCES `users` (`id_u`) ON DELETE CASCADE;

--
-- Constraints for table `shopping_carts`
--
ALTER TABLE `shopping_carts`
  ADD CONSTRAINT `FK_SHOPPING_CART_PRODUCTS` FOREIGN KEY (`id_p`) REFERENCES `products` (`id_p`) ON DELETE CASCADE,
  ADD CONSTRAINT `FK_SHOPPING_CART_USERS` FOREIGN KEY (`id_u`) REFERENCES `users` (`id_u`) ON DELETE CASCADE;

--
-- Constraints for table `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `FK_USERS_PROVINCES` FOREIGN KEY (`id_prov`) REFERENCES `provinces` (`id_p`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
