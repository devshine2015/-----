# 海-盗-王

## WINDOWS:

### How to install:
1. Install Microsoft Visual Studio 2008 for client compile, Install Microsoft Visual Studio 2013 for server compile
2. Install and configure MSQL of any version liked - recommended MSQL 2019 and the guide as follows: https://pko.coffeecup.com/. Don't do anything regarding db accounts (except sa), dbs, ip or more yet - leave that part for later.
3. Install git for windows. Select the cmd.exe options (but no options with added unix tools please).
4. Download the project:
    1. **WARNING: .bat files must have Windows' CR LF line endings - The following will break the build:**
		1. Downloading project files from the web page repository (files will come with Linux line endings).
		2. Using git on a different operating system other than Windows first (files will come with line endings of respective OS - Mac with CR, Linux with LF).
5. Compile the project;
    1. Then cd to the project folder - the following is an example with default name and following previous example:
	```
    cd -----
	```
    2. Type "build.bat" and add the following parameters if needed:
6. (Only if using SQL 2000) Open all .cfg files that are in server folder, and remove any ",1433" you see.

### How to use (assumes build.bat completes successfully once):
1. Start the SQL server (if it isn't by now) and run runall.bat in server folder to start all game server exe's (not applicable to TradeServer and TradeTools yet, they're still being fixed).
2. Run run.bat in client folder to run client.
3. Select the only server available, and put the user name *deguix* and pass *123456* and press Enter (it's a fresh account, no chars are there). The game should be working at this point.