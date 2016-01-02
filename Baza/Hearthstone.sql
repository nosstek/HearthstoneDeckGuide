-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 02 Sty 2016, 23:41
-- Wersja serwera: 5.5.46-0ubuntu0.14.04.2
-- Wersja PHP: 5.5.9-1ubuntu4.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `Hearthstone`
--

-- --------------------------------------------------------

--
-- Zastąpiona struktura widoku `AllCardsView`
--
CREATE TABLE IF NOT EXISTS `AllCardsView` (
`id` int(11)
,`name` varchar(255)
,`description` varchar(255)
,`base_cost` int(11)
,`class` varchar(255)
);
-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Card`
--

CREATE TABLE IF NOT EXISTS `Card` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `base_cost` int(11) NOT NULL DEFAULT '0',
  `overload` int(11) NOT NULL DEFAULT '0',
  `CardType_id` int(11) NOT NULL DEFAULT '1',
  `CardQuality_id` int(11) NOT NULL DEFAULT '1',
  `Class_id` int(11) NOT NULL DEFAULT '10',
  `EffectGroup_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `EffectGroup_id` (`EffectGroup_id`),
  KEY `CardType_id` (`CardType_id`),
  KEY `CardQuality_id` (`CardQuality_id`),
  KEY `Class_id` (`Class_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Zrzut danych tabeli `Card`
--

INSERT INTO `Card` (`id`, `name`, `description`, `base_cost`, `overload`, `CardType_id`, `CardQuality_id`, `Class_id`, `EffectGroup_id`) VALUES
(1, 'Ancestral Healing', 'Restore a minion to full Health and give it Taunt.', 0, 0, 1, 1, 7, NULL),
(2, 'Arcane Explosion', 'Deal 1 damage to all enemy minions.', 2, 0, 1, 1, 3, NULL),
(3, 'Arcane Intellect', 'Draw 2 cards.', 3, 0, 1, 1, 10, NULL),
(4, 'Arcane Missiles', 'Deal 3 damage randomly split among all enemies.', 1, 0, 1, 1, 10, NULL),
(5, 'Arcane Shot', 'Deal 2 damage.', 1, 0, 1, 1, 10, NULL),
(6, 'Assassinate', 'Destroy an enemy minion.', 5, 0, 1, 1, 10, NULL),
(7, 'Backstab', '', 0, 0, 1, 1, 10, NULL),
(8, 'Blessing of Might', 'Give a minion +3 Attack.', 1, 0, 1, 1, 10, NULL),
(9, 'Bloodfen Raptor', NULL, 2, 0, 1, 1, 10, NULL),
(10, 'Boulderfist Ogre', NULL, 6, 0, 1, 1, 10, NULL),
(11, 'Charge', 'Give a friendly minion +2 Attack and Charge.', 3, 0, 1, 1, 10, NULL),
(12, 'Claw', 'Give your hero +2 Attack this turn and 2 Armor.', 1, 0, 1, 1, 10, NULL),
(13, 'Deadly Poison', 'Give your weapon +2 Attack.', 1, 0, 1, 1, 10, NULL),
(14, 'Drain Life', 'Deal 2 damage. Restore 2 Health to your hero.', 3, 0, 1, 1, 10, NULL),
(15, 'Execute', 'Destroy a damaged enemy minion.', 1, 0, 1, 1, 10, NULL);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `CardQuality`
--

CREATE TABLE IF NOT EXISTS `CardQuality` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Zrzut danych tabeli `CardQuality`
--

INSERT INTO `CardQuality` (`id`, `name`) VALUES
(1, 'base'),
(2, 'common'),
(4, 'epic'),
(5, 'legendary'),
(3, 'rare');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `CardType`
--

CREATE TABLE IF NOT EXISTS `CardType` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Zrzut danych tabeli `CardType`
--

INSERT INTO `CardType` (`id`, `name`) VALUES
(2, 'minion'),
(1, 'spell'),
(3, 'weapon');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Class`
--

CREATE TABLE IF NOT EXISTS `Class` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

--
-- Zrzut danych tabeli `Class`
--

INSERT INTO `Class` (`id`, `name`) VALUES
(1, 'druid'),
(2, 'hunter'),
(3, 'mage'),
(4, 'paladin'),
(5, 'priest'),
(6, 'rogue'),
(7, 'shaman'),
(8, 'warlock'),
(9, 'warrior'),
(10, 'none');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Condition`
--

CREATE TABLE IF NOT EXISTS `Condition` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Deck`
--

CREATE TABLE IF NOT EXISTS `Deck` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `Player_id` int(11) NOT NULL,
  `Class_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `Player_id` (`Player_id`),
  KEY `Class_id` (`Class_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=29 ;

--
-- Zrzut danych tabeli `Deck`
--

INSERT INTO `Deck` (`id`, `name`, `Player_id`, `Class_id`) VALUES
(27, 'Newdeck', 15, 1),
(28, 'Newdeck', 1, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Decks_with_cards`
--

CREATE TABLE IF NOT EXISTS `Decks_with_cards` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Deck_id` int(11) NOT NULL,
  `Card_id` int(11) NOT NULL,
  `card_quantity` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `Card_id` (`Card_id`),
  KEY `Deck_id` (`Deck_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=140 ;

--
-- Zrzut danych tabeli `Decks_with_cards`
--

INSERT INTO `Decks_with_cards` (`id`, `Deck_id`, `Card_id`, `card_quantity`) VALUES
(133, 27, 1, 1),
(134, 27, 2, 1),
(135, 27, 3, 1),
(136, 28, 3, 1),
(137, 28, 9, 2),
(138, 28, 8, 1),
(139, 28, 6, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Effect`
--

CREATE TABLE IF NOT EXISTS `Effect` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `EffectType_id` int(11) NOT NULL,
  `Target_id` int(11) NOT NULL,
  `power` int(11) NOT NULL,
  `duration` int(11) NOT NULL,
  `Condition_id` int(11) NOT NULL,
  `Minion_id` int(11) DEFAULT NULL,
  `Weapon_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `Minion_id` (`Minion_id`,`Weapon_id`),
  KEY `Weapon_id` (`Weapon_id`),
  KEY `EffectType_id` (`EffectType_id`),
  KEY `TargetGroup_id` (`Target_id`),
  KEY `Condition_id` (`Condition_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `EffectGroup`
--

CREATE TABLE IF NOT EXISTS `EffectGroup` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `EffectGroups_with_effects`
--

CREATE TABLE IF NOT EXISTS `EffectGroups_with_effects` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `EffectGroup_id` int(11) NOT NULL,
  `Effect_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `EffectGroup_id` (`EffectGroup_id`),
  KEY `Effect_id` (`Effect_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `EffectType`
--

CREATE TABLE IF NOT EXISTS `EffectType` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Minion`
--

CREATE TABLE IF NOT EXISTS `Minion` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `base_cost` int(11) NOT NULL,
  `attack` int(11) NOT NULL,
  `durability` int(11) NOT NULL,
  `MinionType_id` int(11) NOT NULL DEFAULT '0',
  `spell_damage` int(11) NOT NULL,
  `taunt` tinyint(1) NOT NULL,
  `charge` tinyint(1) NOT NULL,
  `windfury` tinyint(1) NOT NULL,
  `shield` tinyint(1) NOT NULL,
  `stealth` tinyint(1) NOT NULL DEFAULT '0',
  `EffectGroup_OnAttack` int(11) NOT NULL,
  `EffectGroup_OnDamage` int(11) NOT NULL,
  `EffectGroup_OnHeal` int(11) NOT NULL,
  `EffectGroup_OnBattlecry` int(11) NOT NULL,
  `EffectGroup_OnDeathrattle` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `EffectGroup_OnAttack` (`EffectGroup_OnAttack`),
  KEY `EffectGroup_OnDamage` (`EffectGroup_OnDamage`),
  KEY `EffectGroup_OnHeal` (`EffectGroup_OnHeal`),
  KEY `EffectGroup_OnBattlecry` (`EffectGroup_OnBattlecry`),
  KEY `EffectGroup_OnDeathrattle` (`EffectGroup_OnDeathrattle`),
  KEY `MinionType_id` (`MinionType_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `MinionType`
--

CREATE TABLE IF NOT EXISTS `MinionType` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Player`
--

CREATE TABLE IF NOT EXISTS `Player` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  UNIQUE KEY `email` (`email`),
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Zrzut danych tabeli `Player`
--

INSERT INTO `Player` (`id`, `name`, `password`, `email`) VALUES
(1, 'tomasz', 'kassa', 'tomasz.kassa@gmail.com'),
(2, 'lukasz', 'jablonski', 'lukasz.jablonski@gmail.com'),
(15, 'test', 'test', 'test@test.test');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Players_with_cards`
--

CREATE TABLE IF NOT EXISTS `Players_with_cards` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Player_id` int(11) NOT NULL,
  `Card_id` int(11) NOT NULL,
  `card_quantity` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `Card_id` (`Card_id`),
  KEY `Player_id` (`Player_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=97 ;

--
-- Zrzut danych tabeli `Players_with_cards`
--

INSERT INTO `Players_with_cards` (`id`, `Player_id`, `Card_id`, `card_quantity`) VALUES
(84, 15, 1, 1),
(85, 15, 2, 1),
(86, 15, 3, 1),
(87, 15, 4, 1),
(88, 15, 5, 1),
(89, 15, 6, 1),
(90, 15, 7, 1),
(91, 1, 4, 1),
(92, 1, 3, 1),
(93, 1, 2, 1),
(94, 1, 6, 1),
(95, 1, 9, 2),
(96, 1, 8, 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Target`
--

CREATE TABLE IF NOT EXISTS `Target` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Weapon`
--

CREATE TABLE IF NOT EXISTS `Weapon` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `attack` int(11) NOT NULL,
  `durability` int(11) NOT NULL,
  `windfury` tinyint(1) NOT NULL DEFAULT '0',
  `EffectGroup_OnAttack` int(11) NOT NULL,
  `EffectGroup_OnBattlecry` int(11) NOT NULL,
  `EffectGroup_OnDeathrattle` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `EffectGroup_OnAttack` (`EffectGroup_OnAttack`),
  KEY `EffectGroup_OnBattlecry` (`EffectGroup_OnBattlecry`),
  KEY `EffectGroup_OnDeathrattle` (`EffectGroup_OnDeathrattle`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Struktura widoku `AllCardsView`
--
DROP TABLE IF EXISTS `AllCardsView`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `AllCardsView` AS select `Card`.`id` AS `id`,`Card`.`name` AS `name`,`Card`.`description` AS `description`,`Card`.`base_cost` AS `base_cost`,`Class`.`name` AS `class` from (`Card` join `Class`) where (`Card`.`Class_id` = `Class`.`id`) order by `Card`.`name`;

--
-- Ograniczenia dla zrzutów tabel
--

--
-- Ograniczenia dla tabeli `Card`
--
ALTER TABLE `Card`
  ADD CONSTRAINT `Card_ibfk_1` FOREIGN KEY (`EffectGroup_id`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Card_ibfk_2` FOREIGN KEY (`CardType_id`) REFERENCES `CardType` (`id`),
  ADD CONSTRAINT `Card_ibfk_3` FOREIGN KEY (`CardQuality_id`) REFERENCES `CardQuality` (`id`),
  ADD CONSTRAINT `Card_ibfk_4` FOREIGN KEY (`Class_id`) REFERENCES `Class` (`id`);

--
-- Ograniczenia dla tabeli `Deck`
--
ALTER TABLE `Deck`
  ADD CONSTRAINT `Deck_ibfk_1` FOREIGN KEY (`Player_id`) REFERENCES `Player` (`id`),
  ADD CONSTRAINT `Deck_ibfk_2` FOREIGN KEY (`Class_id`) REFERENCES `Class` (`id`);

--
-- Ograniczenia dla tabeli `Decks_with_cards`
--
ALTER TABLE `Decks_with_cards`
  ADD CONSTRAINT `Decks_with_cards_ibfk_1` FOREIGN KEY (`Deck_id`) REFERENCES `Deck` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `Decks_with_cards_ibfk_2` FOREIGN KEY (`Card_id`) REFERENCES `Card` (`id`) ON DELETE CASCADE;

--
-- Ograniczenia dla tabeli `Effect`
--
ALTER TABLE `Effect`
  ADD CONSTRAINT `Effect_ibfk_1` FOREIGN KEY (`Minion_id`) REFERENCES `Minion` (`id`),
  ADD CONSTRAINT `Effect_ibfk_2` FOREIGN KEY (`Weapon_id`) REFERENCES `Weapon` (`id`),
  ADD CONSTRAINT `Effect_ibfk_3` FOREIGN KEY (`EffectType_id`) REFERENCES `EffectType` (`id`),
  ADD CONSTRAINT `Effect_ibfk_5` FOREIGN KEY (`Condition_id`) REFERENCES `Condition` (`id`),
  ADD CONSTRAINT `Effect_ibfk_6` FOREIGN KEY (`Target_id`) REFERENCES `Target` (`id`);

--
-- Ograniczenia dla tabeli `EffectGroups_with_effects`
--
ALTER TABLE `EffectGroups_with_effects`
  ADD CONSTRAINT `EffectGroups_with_effects_ibfk_1` FOREIGN KEY (`Effect_id`) REFERENCES `Effect` (`id`),
  ADD CONSTRAINT `EffectGroups_with_effects_ibfk_2` FOREIGN KEY (`EffectGroup_id`) REFERENCES `EffectGroup` (`id`);

--
-- Ograniczenia dla tabeli `Minion`
--
ALTER TABLE `Minion`
  ADD CONSTRAINT `Minion_ibfk_1` FOREIGN KEY (`EffectGroup_OnAttack`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Minion_ibfk_2` FOREIGN KEY (`EffectGroup_OnDamage`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Minion_ibfk_3` FOREIGN KEY (`EffectGroup_OnHeal`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Minion_ibfk_4` FOREIGN KEY (`EffectGroup_OnBattlecry`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Minion_ibfk_5` FOREIGN KEY (`EffectGroup_OnDeathrattle`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Minion_ibfk_6` FOREIGN KEY (`MinionType_id`) REFERENCES `MinionType` (`id`);

--
-- Ograniczenia dla tabeli `Players_with_cards`
--
ALTER TABLE `Players_with_cards`
  ADD CONSTRAINT `Players_with_cards_ibfk_1` FOREIGN KEY (`Card_id`) REFERENCES `Card` (`id`),
  ADD CONSTRAINT `Players_with_cards_ibfk_2` FOREIGN KEY (`Player_id`) REFERENCES `Player` (`id`);

--
-- Ograniczenia dla tabeli `Weapon`
--
ALTER TABLE `Weapon`
  ADD CONSTRAINT `Weapon_ibfk_1` FOREIGN KEY (`EffectGroup_OnAttack`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Weapon_ibfk_2` FOREIGN KEY (`EffectGroup_OnBattlecry`) REFERENCES `EffectGroup` (`id`),
  ADD CONSTRAINT `Weapon_ibfk_3` FOREIGN KEY (`EffectGroup_OnDeathrattle`) REFERENCES `EffectGroup` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
