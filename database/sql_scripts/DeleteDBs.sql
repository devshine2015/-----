USE [master]
GO
IF EXISTS(select * from sys.databases where name='accountserver')
DROP DATABASE [accountserver]
GO
IF EXISTS(select * from sys.databases where name='gamedb')
DROP DATABASE [gamedb]
GO
IF EXISTS(select * from sys.databases where name='tradedb')
DROP DATABASE [tradedb]
GO
DROP LOGIN pko_account;
DROP LOGIN pko_game;
DROP LOGIN pko_trade;
GO