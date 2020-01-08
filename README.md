# Bookstore

> Homework 2019/12/13-2020/01/08

## TODO

### 1. Data storage in files

### 2. Command support

#### 1. User

```shell
load [destination]
exit
su [user-id] [passwd]
logout
useradd [user-id] [passwd] [7/3/1] [name]
register [user-id] [passwd] [name]
delete [user-id]
passwd [user-id] [old-passwd(if not root)] [new-passwd]
```

#### 2. Book operation

```shell
select [ISBN]
modify -ISBN=[ISBN] -name=[name] -author=[author] -keyword=[keyword] -price=[price]
import [quantity] [cost_price(in total)]
show -ISBN=[ISBN] -name=[name] -author=[author] -keyword=[keyword]
show finance [time]
buy [ISBN] [quantity]
```

#### 3. Report

```shell
report finance
report employee
log
report myself
```

### 3. GUI

## DONE

### 0. None
