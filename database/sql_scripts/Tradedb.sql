USE [master]
GO
CREATE DATABASE [tradedb]
GO
/****** Wolfendev ******/
/******  Script   ******/
USE [tradedb]
GO
/****** Objeto:  Table [dbo].[AccountInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:05:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[AccountInfo](
	[accID] [bigint] NOT NULL,
	[accName] [varchar](64) NOT NULL,
	[Money] [bigint] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
/****** Objeto:  Table [dbo].[AfficheInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:06:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[AfficheInfo](
	[affiID] [bigint] IDENTITY(1,1) NOT NULL,
	[affiTitle] [varchar](256) NOT NULL,
	[comID] [varchar](64) NOT NULL,
	[affiTime] [bigint] NOT NULL,
	[isDel] [int] NOT NULL,
	[delTime] [bigint] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
/****** Objeto:  Table [dbo].[ClassInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:06:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ClassInfo](
	[clsID] [bigint] IDENTITY(1,1) NOT NULL,
	[clsName] [varchar](64) NOT NULL,
	[parentID] [bigint] NOT NULL,
	[buildTime] [bigint] NOT NULL,
	[isDel] [int] NOT NULL,
	[delTime] [bigint] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Pet',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Leveling',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Teleport',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Forging',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Quest',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Decoration',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Grocery',0,0,0,0)
insert into ClassInfo (clsName,parentID,buildTime,isDel,delTime) values('Promotion',0,0,0,0)

/****** Objeto:  Table [dbo].[ItemInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:07:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ItemInfo](
	[comID] [bigint] NOT NULL,
	[itemID] [bigint] NOT NULL,
	[itemNum] [bigint] NOT NULL,
	[itemFlute] [int] NOT NULL,
	[itemAttrID1] [int] NOT NULL,
	[itemAttrVal1] [int] NOT NULL,
	[itemAttrID2] [int] NOT NULL,
	[itemAttrVal2] [int] NOT NULL,
	[itemAttrID3] [int] NOT NULL,
	[itemAttrVal3] [int] NOT NULL,
	[itemAttrID4] [int] NOT NULL,
	[itemAttrVal4] [int] NOT NULL,
	[itemAttrID5] [int] NOT NULL,
	[itemAttrVal5] [int] NOT NULL
) ON [PRIMARY]
/****** Objeto:  Table [dbo].[MailInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:07:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[MailInfo](
	[mlID] [bigint] IDENTITY(1,1) NOT NULL,
	[mlTitle] [varchar](50) NOT NULL,
	[mlInformation] [varchar](512) NOT NULL,
	[actID] [bigint] NOT NULL,
	[actName] [varchar](64) NOT NULL,
	[chaID] [bigint] NOT NULL,
	[chaName] [varchar](64) NOT NULL,
	[sndTime] [bigint] NOT NULL,
	[servID] [int] NOT NULL,
	[replyGM] [int] NOT NULL CONSTRAINT [DF_MailInfo_replyGM]  DEFAULT ((0)),
	[replyTime] [bigint] NOT NULL CONSTRAINT [DF_MailInfo_replyTime]  DEFAULT ((0)),
	[replyInformation] [varchar](512) NOT NULL CONSTRAINT [DF_MailInfo_replyInformation]  DEFAULT (''),
	[GMreaderTime] [bigint] NOT NULL CONSTRAINT [DF_MailInfo_readerGM]  DEFAULT ((0)),
 CONSTRAINT [PK_MailInfo] PRIMARY KEY CLUSTERED 
(
	[mlID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
/****** Objeto:  Table [dbo].[OperateHistory]    Fecha de la secuencia de comandos: 01/27/2015 09:07:47 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[OperateHistory](
	[tradeID] [bigint] IDENTITY(1,1) NOT NULL,
	[tradeTime] [bigint] NULL,
	[serveID] [bigint] NULL,
	[orderID] [bigint] NULL,
	[accID] [bigint] NULL,
	[type] [int] NULL,
	[Field1] [varchar](128) NULL,
	[Field2] [varchar](128) NULL,
	[Field3] [varchar](128) NULL,
	[Field4] [varchar](256) NULL,
	[Field5] [varchar](256) NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
/****** Objeto:  Table [dbo].[Safety]    Fecha de la secuencia de comandos: 01/27/2015 09:08:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Safety](
	[Sid] [bigint] NOT NULL,
	[Ip] [varchar](32) NOT NULL,
	[Passwd] [varchar](64) NOT NULL,
	[Type] [int] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
insert into Safety (Sid,Ip,Passwd,Type) values(1,'127.0.0.1','2b798b2ee7c3b79535d83918d3e824aa2485c8a302964893086e381a5dd466d6',0)
/****** Objeto:  Table [dbo].[StoreInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:10:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[StoreInfo](
	[comID] [bigint] IDENTITY(1,1) NOT NULL,
	[comName] [varchar](64) NOT NULL,
	[comClass] [bigint] NOT NULL,
	[comTime] [bigint] NOT NULL,
	[comPrice] [bigint] NOT NULL,
	[comRemack] [varchar](512) NOT NULL,
	[comNumber] [int] NOT NULL,
	[comExpire] [bigint] NOT NULL,
	[isDel] [int] NOT NULL,
	[delTime] [bigint] NOT NULL,
	[isHot] [int] NOT NULL,
	[beginTime] [bigint] NOT NULL CONSTRAINT [DF_StoreInfo_beginTime]  DEFAULT ((0))
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
/****** Objeto:  Table [dbo].[VIPInfo]    Fecha de la secuencia de comandos: 01/27/2015 09:10:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[VIPInfo](
	[vipID] [int] NOT NULL,
	[vipPrice] [int] NOT NULL
) ON [PRIMARY]
