BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Player" (
	"ID"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	"Name"	TEXT NOT NULL,
	"Lastname"	TEXT NOT NULL,
	"Username"	TEXT NOT NULL,
	"Password"	REAL NOT NULL
);
INSERT INTO "Player" VALUES (0,'','','','');
INSERT INTO "Player" VALUES (1,'Amina','Kusljugic','Minkica','amina123');
INSERT INTO "Player" VALUES (2,'Emir','Karic','Emir','emir123');
INSERT INTO "Player" VALUES (3,'Ahmed','Kusljugic','Smaug',1234.0);
INSERT INTO "Player" VALUES (5,'','','','');
INSERT INTO "Player" VALUES (6,'Lejla','Bjelic','lejla',8520.0);
INSERT INTO "Player" VALUES (7,'dzenan','bjelic','dzeno',258.0);
INSERT INTO "Player" VALUES (8,'Kenan','Kusljugic','Keno',123.0);
INSERT INTO "Player" VALUES (9,'Munevera','Kusljugic','Mumka',0.0);
INSERT INTO "Player" VALUES (10,'Mevlida','Bjelic','Mida',1111.0);
INSERT INTO "Player" VALUES (11,'Bahra','Karic','Bahra',123.0);
INSERT INTO "Player" VALUES (12,'Fahro','Karic','Fahro',1234.0);
COMMIT;
