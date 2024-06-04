-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Cze 04, 2024 at 09:08 PM
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
(36, 9);

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
(40, NULL, 'Dodano nowy produkt: id=36, id');

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
(36, 'D:/shop/shop/imgs/TTMrVo.png');

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
(26, 14, 'Buty', 249.99, 1, '2024-06-01', 'Nowe buty markowe.', 1),
(27, 14, 'Piłka do siatkówki', 150.00, 1, '2024-06-01', 'Nowe piłki Dippsta', 1),
(28, 17, 'Monitor 24\'', 449.99, 1, '2024-06-01', 'Monitory 60 Hz', 1),
(29, 17, 'Komplet opon zimowych', 1200.00, 0, '2024-06-01', 'Opony na zime dobrej firmy', 1),
(30, 19, 'Krem na noc', 34.99, 1, '2024-06-01', 'Krem na noc. Bardzo dobry.', 1),
(36, 25, 'Piłka Tango 2012', 33.33, 2, '2024-06-02', 'Piłka Jakuba Błaszczykowskiego', 0);

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
(17, 30, 2, 'Odbiór osobisty na UKSW', 'Nasielsk Leśna 13', '2024-06-01 12:24:15');

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
(14, 'Maciej', 'Nowak', 'nowa@nowa', '123123', 16, '12-120', 'Warszawa', 'Wóycickiego', 1),
(15, 'Andrzej', 'Kowalski', 'kowal@kowal', '123321', 14, '00-000', 'Poznań', 'Krakowska 5', 1),
(17, 'Julianna', 'Bobko', 'bob@gmail.com', '111222', 7, '05-190', 'Nasielsk', 'Leśna 13', 1),
(18, 'Mirosław', 'Kuźnicki', 'miro@onet.pl', '321321', 16, '12-122', 'Płock', 'Basenowa 22', 1),
(19, 'Zuzanna', 'Pietrak', 'zupie@wp.pl', '123123123', 5, '15-190', 'Chrząszczyrzewoszyce', 'Duża 5', 1),
(25, 'Maciej', 'Grzywacki', 'grzywa@gmail.com', '123321123', 9, '12-303', 'Warszawa', 'Dworzec Gdański 15', 1);

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
  MODIFY `id` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=41;

--
-- AUTO_INCREMENT for table `products`
--
ALTER TABLE `products`
  MODIFY `id_p` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=37;

--
-- AUTO_INCREMENT for table `provinces`
--
ALTER TABLE `provinces`
  MODIFY `id_p` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id_u` int(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

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
