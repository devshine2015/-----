USE [master]
GO
CREATE DATABASE [accountserver]
GO
USE [accountserver]
GO
/****** Object:  Table [dbo].[account_charge]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[account_charge](
	[id] [int] NOT NULL,
	[charge_flag] [int] NULL,
	[charge_begin_tick] [int] NULL,
	[charge_end_tick] [int] NULL,
	[saves] [int] NULL,
 CONSTRAINT [PK_account_charge] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[account_login]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[account_login](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](50) NULL,
	[password] [varchar](50) NULL,
	[sid] [int] NOT NULL,
	[login_status] [int] NULL,
	[enable_login_tick] [bigint] NULL,
	[login_group] [varchar](50) NULL,
	[last_login_time] [datetime] NULL,
	[last_logout_time] [datetime] NULL,
	[last_login_ip] [varchar](50) NULL,
	[enable_login_time] [datetime] NULL,
	[total_live_time] [bigint] NOT NULL,
	[last_login_mac] [varchar](50) NULL,
	[ban] [int] NULL,
	[q1] [varchar](50) NULL,
	[a1] [varchar](50) NULL,
	[QQ] [varchar](50) NULL,
	[tname] [varchar](50) NULL,
	[card] [varchar](18) NULL,
	[tel] [varchar](50) NULL,
	[anquan] [varchar](50) NULL,
	[email] [varchar](50) NULL,
 CONSTRAINT [PK_account_login] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [IX_account_login] UNIQUE NONCLUSTERED 
(
	[name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [IX_account_login_name] UNIQUE NONCLUSTERED 
(
	[name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[act_album]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[act_album](
	[act_id] [int] IDENTITY(1,1) NOT NULL,
	[act_name] [varchar](50) NULL,
	[SessionKey] [varchar](50) NULL,
	[create_time] [datetime] NULL,
	[update_time] [datetime] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[GameDBServerList]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[GameDBServerList](
	[server_section] [int] NOT NULL,
	[server_ip] [varchar](128) NOT NULL,
	[server_uid] [varchar](128) NOT NULL,
	[server_pwd] [varchar](128) NOT NULL,
	[server_db] [varchar](128) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LogRandomAccount]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LogRandomAccount](
	[accountName] [varchar](50) NOT NULL,
	[addDate] [datetime] NULL,
	[expireDate] [datetime] NULL,
	[ip] [varchar](15) NULL,
	[plainPassword] [varchar](32) NULL,
 CONSTRAINT [PK_LogRandomAccount] PRIMARY KEY CLUSTERED 
(
	[accountName] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[safety]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[safety](
	[aid] [bigint] IDENTITY(1,1) NOT NULL,
	[allowIP] [varchar](32) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TradeRecord]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TradeRecord](
	[record_id] [varchar](50) NOT NULL,
	[record_message] [int] NOT NULL,
	[record_section] [int] NOT NULL,
	[record_info] [varchar](4000) NOT NULL,
	[record_time] [datetime] NOT NULL,
	[ret_info] [varchar](4000) NOT NULL,
	[ret_time] [datetime] NOT NULL,
	[state] [int] NOT NULL,
	[flow_id] [varchar](50) NULL,
	[production_id] [varchar](50) NULL,
 CONSTRAINT [IX_TradeRecord] UNIQUE NONCLUSTERED 
(
	[record_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[user_log]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[user_log](
	[log_id] [int] IDENTITY(1,1) NOT NULL,
	[user_id] [int] NOT NULL,
	[user_name] [varchar](50) NOT NULL,
	[login_time] [datetime] NULL,
	[logout_time] [datetime] NULL,
	[login_ip] [varchar](20) NULL,
 CONSTRAINT [PK_user_log] PRIMARY KEY CLUSTERED 
(
	[log_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UserAccountLogin]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UserAccountLogin](
	[Date] [datetime] NULL,
	[AllAccount] [int] NULL,
	[ActionAccount] [int] NULL
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_sid]  DEFAULT (0) FOR [sid]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_login_status]  DEFAULT (0) FOR [login_status]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_enable_login_tick]  DEFAULT (0) FOR [enable_login_tick]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_last_login_time]  DEFAULT (getdate()) FOR [last_login_time]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_last_logout_time]  DEFAULT (getdate()) FOR [last_logout_time]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_enable_login_time]  DEFAULT ('2001-1-1 1:1:1') FOR [enable_login_time]
GO
ALTER TABLE [dbo].[account_login] ADD  CONSTRAINT [DF_account_login_total_live_time]  DEFAULT (0) FOR [total_live_time]
GO
ALTER TABLE [dbo].[act_album] ADD  DEFAULT (getdate()) FOR [create_time]
GO
ALTER TABLE [dbo].[act_album] ADD  DEFAULT (getdate()) FOR [update_time]
GO
/****** Object:  StoredProcedure [dbo].[Create_GameAccount]    Script Date: 1/1/2020 2:02:06 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[Create_GameAccount] 
	@Prefix varchar(50)='KopTest' ,--用户名前缀
	@SartNo int = 0, --开始序号
	@Number int = 1, --帐号,
	@TempletID int --样版角色ID
AS
BEGIN
	
	SET NOCOUNT ON;
	DECLARE @AccountID int --帐号ID
	DECLARE @CharacterID int --角色ID
	DECLARE @UserName varchar(50) --用户名称
	DECLARE @CharacterName varchar(50) --角色名称
	DECLARE @CharacterList varchar(100) --角色ID列表
	DECLARE @Password varchar(50) --用户密码
	DECLARE @KitBagID int --临时背包ID
	DECLARE @KitBagIDTemp int --临时背包ID
	DECLARE @BankID int --银行ID
	DECLARE @MapMaskID int
	DECLARE @No int --序号
	

	BEGIN TRAN CREATEACCOUNTTRAN

	SET @Password = 'E10ADC3949BA59ABBE56E057F20F883E' --123456
	SET @No = 0
	WHILE (@No < @Number)
	BEGIN
		SET @CharacterList = '0'
		SET @UserName = @Prefix + '' + CAST( (@SartNo + @No) as varchar)
		--创建帐号
		INSERT INTO AccountServer.dbo.account_login(name,password)
			VALUES(@UserName,@Password);
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK
		SELECT @AccountID = @@IDENTITY
		--PRINT @AccountID

		--创建角色
		INSERT INTO GameDB.dbo.account(act_id,act_name,gm,cha_ids,password)
			VALUES(@AccountID,@UserName,0,'0',@Password)
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK
		
		
		INSERT INTO GameDB.dbo.character(act_id,cha_name,bank)
			VALUES(@AccountID,@UserName,'')
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK
		SELECT @CharacterID = @@IDENTITY	
		SET @CharacterList  = CAST( @CharacterID as varchar) + ';'
		--PRINT @CharacterList

		--背包ID
		INSERT INTO GameDB.dbo.Resource(cha_id,type_id,content)
		SELECT @CharacterID,1,content
		FROM GameDB.dbo.Resource 
		WHERE cha_id=@TempletID AND type_id=1
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK			
		SELECT @KitBagID = @@IDENTITY
		PRINT @KitBagID

		--银行ID
		INSERT INTO GameDB.dbo.Resource(cha_id,type_id,content)
		SELECT @CharacterID,2,content
		FROM GameDB.dbo.Resource 
		WHERE cha_id=@TempletID AND type_id=2
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK
		SELECT @BankID = @@IDENTITY
		
		--临时背包ID
		INSERT INTO GameDB.dbo.Resource(cha_id,type_id,content)
		SELECT @CharacterID,3,content
		FROM GameDB.dbo.Resource 
		WHERE cha_id=@TempletID AND type_id=3
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK
		SELECT @KitBagIDTemp = @@IDENTITY
			
		--
		INSERT INTO GameDB.dbo.map_mask(cha_id,content1,content2,content3,content4,content5)
			VALUES(@CharacterID,'0','0','0','0','0')
		SELECT @MapMaskID = @@IDENTITY
		UPDATE GameDB.dbo.account SET cha_ids = @CharacterList 
			WHERE act_id =@AccountID
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK

		--更新角色信息
		
		UPDATE GameDB.dbo.character SET 
			kitbag=@KitBagID,
			bank = @BankID,
			kitbag_tmp = @KitBagIDTemp,
			map_mask = @MapMaskID,
			icon = A.A_icon,
			version = A.A_version,
			hp = A.A_hp,
			sp = A.A_sp,
			ap = A.A_ap,
			[str] = A.A_str,
			dex = A.A_dex,
			agi = A.A_agi,
			con = A.A_con,
			sta = A.A_sta,
			luk = A.A_luk,
			sail_lv = A.A_sail_lv,
			live_lv = A.A_live_lv,
			job = A.A_job,
			degree = A.A_degree,
			map = A.A_map,
			map_x = A.A_map_x,
			map_y = A.A_map_y,
			radius = A.A_radius,
			angle = A.A_angle,
			look = A.A_look,
			kb_capacity = A.A_kb_capacity,
			skillbag = A.A_skillbag,
			shortcut = A.A_shortcut,
			mission = A.A_mission,
			misrecord = A.A_misrecord,
			mistrigger = A.A_mistrigger,
			miscount = A.A_miscount,
			birth = A.A_birth,
			login_cha = A.A_login_cha,	
			live_tp = A.A_live_tp,					
			main_map = A.A_main_map,
			skill_state = A.A_skill_state,
			estop = A.A_estop,
			estoptime = A.A_estoptime,
			kb_locked = A.A_kb_locked,
			credit = A.A_credit,
			store_item = A.A_store_item,
			extend = A.A_extend
		FROM (
			SELECT 
				motto ,
				icon AS A_icon,
				version as A_version,
				pk_ctrl as A_pk_ctrl,
				job as A_job,
				degree as A_degree,
				[exp] as A_exp,
				hp as A_hp,
				sp as A_sp,
				ap as A_ap,
				tp as A_tp,
				gd as A_gd,
				[str] as A_str,

				dex as A_dex,
				agi as A_agi,
				con as A_con,
				sta as A_sta,
				luk as A_luk,
				sail_lv as A_sail_lv,
				sail_exp as A_sail_exp,
				sail_left_exp as A_sail_left_exp,
				live_lv as A_live_lv,
				live_exp as A_live_exp,
				map as A_map,
				map_x as A_map_x,
				map_y as A_map_y,
				radius as A_radius,
				angle as A_angle,
				look as A_look,
				kb_capacity as A_kb_capacity,
				kitbag as A_kitbag,
				skillbag as A_skillbag,
				shortcut as A_shortcut,
				mission as A_mission,
				misrecord as A_misrecord,
				mistrigger as A_mistrigger,
				miscount as A_miscount,
				birth as A_birth,
				login_cha as A_login_cha,
				live_tp as A_live_tp,
				map_mask as A_map_mask,
				main_map as A_main_map,
				skill_state as A_skill_state,
				estop as A_estop,
				estoptime as A_estoptime,
				kb_locked as A_kb_locked,
				credit as A_credit,
				store_item as A_store_item,
				extend as A_extend
			FROM GameDB.dbo.character
			WHERE cha_id = @TempletID 
			) AS A
		WHERE cha_id = @CharacterID			
		IF (@@ERROR <> 0 ) GOTO ERROR_ROLLBACK

		SET @No = @No + 1
	END
	
	COMMIT TRAN CREATEACCOUNTTRAN
	PRINT '生成完成！'
	GOTO EXIT_TRAN
	
	ERROR_ROLLBACK:
		ROLLBACK TRAN CREATEACCOUNTTRAN
		PRINT '生成失败!'
	
	EXIT_TRAN:
	
	
	SET NOCOUNT OFF;
END

GO
USE [master]
GO
ALTER DATABASE [accountserver] SET  READ_WRITE 
GO
