@echo Rebuilding all dbs from scratch
@echo ----------------------------------------
@echo SQLCMD will prompt you for the SA user password.
@echo It's needed to rebuild the 3 DBs used by this project:
@echo - AccountServer
@echo - GameDB
@echo - TradeServer
@echo 
@echo Also all SQL errors will be shown below
@echo ----------------------------------------
rem made it inline for now to make it only ask password once
rem will need some readjusting later

@sqlcmd -X 1 -U sa -d "master" -i "DeleteDBs.sql" -i "AccountServer.sql" -i "GameDB.sql" -i "Guild.sql" -i "CrystalTrade.sql" -i "Tradedb.sql" -i "CreateLogins.sql" -i "CreateInGameAccount.sql"

rem sqlcmd -X 1 -U sa -d "master" -i "DeleteDBs.sql"
rem sqlcmd -X 1 -U sa -d "master" -i "AccountServer.sql" -i "GameDB.sql" -i "Guild.sql" -i "Tradedb.sql"
rem sqlcmd -X 1 -U sa -d "master" -i "CreateLogins.sql"
rem sqlcmd -X 1 -U sa -d "master" -i "CreateInGameAccount.sql"
rem sqlcmd -X 1 -U sa -d "master" -i "CrystalTrade.sql"
@echo ----------------------------------------