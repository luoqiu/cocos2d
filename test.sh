#!/bin/bash 
echo $1 $2 $3 
sqlite3 demo.db << EOF
create table $1 (ID INTEGER,word text);
insert into $1 values($2,$3);

.quit
EOF
