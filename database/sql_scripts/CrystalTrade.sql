USE [GameDB]
GO
DROP TABLE [dbo].[CrystalTrade];
/****** Object:  Table [dbo].[CrystalTrade] ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[CrystalTrade](
	[cha_id] [bigint] IDENTITY(1,1) NOT NULL,
	[cha_name] [varchar](50) NOT NULL,
	[act_name] [varchar](50) NOT NULL,
	[BusinessID] [bigint] NOT NULL,
	[Totalnum] [bigint] NOT NULL,
	[crystal_num] [bigint] NOT NULL,
	[crystal_price] [bigint] NOT NULL,
	[createtime] [datetime] NOT NULL,
	[tradetype] [bigint] NOT NULL,
	[ishang] [bigint] NOT NULL,
	[tempcoins] [bigint] NOT NULL,
 CONSTRAINT [PK_CrystalTrade] PRIMARY KEY CLUSTERED 
(
	[cha_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_cha_name]  DEFAULT (('')) FOR [cha_name]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_act_name]  DEFAULT (('')) FOR [act_name]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_BusinessID]  DEFAULT ((0)) FOR [BusinessID]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_Totalnum]  DEFAULT ((0)) FOR [Totalnum]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_crystal_num]  DEFAULT ((0)) FOR [crystal_num]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_crystal_price]  DEFAULT ((0)) FOR [crystal_price]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_createtime]  DEFAULT (('2001-01-01')) FOR [createtime]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_tradetype]  DEFAULT ((0)) FOR [tradetype]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_ishang]  DEFAULT ((0)) FOR [ishang]
GO
ALTER TABLE [dbo].[CrystalTrade] ADD  CONSTRAINT [DF_CrystalTrade_tempcoins]  DEFAULT ((0)) FOR [tempcoins]
GO