USE AccountServer;
INSERT INTO account_login (name, password) VALUES ('deguix', 'E10ADC3949BA59ABBE56E057F20F883E');
INSERT INTO account_login (name, password) VALUES ('deguix2', 'E10ADC3949BA59ABBE56E057F20F883E');
USE GameDB;
INSERT INTO account (act_id, act_name, gm) VALUES ((SELECT ISNULL(MAX(act_id) + 1,1) FROM account), 'deguix', 99);
INSERT INTO account (act_id, act_name, gm) VALUES ((SELECT ISNULL(MAX(act_id) + 1,1) FROM account), 'deguix2', 99);