CREATE TABLE ORGANIZATION (
	CODE CHAR(5) PRIMARY KEY,
	NAME CHAR(15)
);

CREATE TABLE EMPLOYEE (
	CODE CHAR(5) PRIMARY KEY,
	NAME CHAR(20),
	ADDRESS CHAR(25),
	CITY CHAR(20),
	BASIC INTEGER,
	JOIN_DATE DATE DEFAULT NULL,
	DEPARTMENT_CODE CHAR(5),
	GRADE CHAR(1),
	FOREIGN KEY (DEPARTMENT_CODE)
		REFERENCES ORGANIZATION(CODE)
		ON DELETE RESTRICT,
	CONSTRAINT BASIC_RANGE CHECK (BASIC >= 5000 AND BASIC <= 9000),
	CONSTRAINT GRADE_RANGE CHECK (GRADE IN ('A', 'B', 'C')),
	CONSTRAINT NAME_RANGE CHECK (NAME = UPPER(NAME))
);

CREATE TABLE LEAVES (
	EMPLOYEE_CODE CHAR(5),
	FROM_DATE DATE,
	UPTO_DATE DATE,
	TYPE CHAR(2),
	PRIMARY KEY (EMPLOYEE_CODE, FROM_DATE),
	FOREIGN KEY (EMPLOYEE_CODE)
		REFERENCES EMPLOYEE(CODE)
		ON DELETE CASCADE,
	CONSTRAINT TYPE_RANGE CHECK (TYPE IN ('CL', 'EL', 'ML'))
);

INSERT INTO ORGANIZATION(CODE, NAME) VALUES ('D01','PERSONNEL');
INSERT INTO ORGANIZATION(CODE, NAME) VALUES ('D02','PRODUCTION');
INSERT INTO ORGANIZATION(CODE, NAME) VALUES ('D03','PURCHASE');
INSERT INTO ORGANIZATION(CODE, NAME) VALUES ('D04','FINANCE');
INSERT INTO ORGANIZATION(CODE, NAME) VALUES ('D05','RESEARCH');

INSERT INTO EMPLOYEE(CODE, NAME, ADDRESS, CITY, BASIC, JOIN_DATE,  DEPARTMENT_CODE, GRADE)

CREATE TABLE MONEY AS
	SELECT EMPLOYEE.CODE AS CODE, EMPLOYEE.NAME AS EMPLOYEE_NAME, ORGANIZATION.NAME AS DEPARTMENT_NAME, BASIC
	FROM EMPLOYEE, ORGANIZATION;

ALTER TABLE MONEY
	ADD PRIMARY KEY (CODE);

INSERT INTO MONEY(CODE, EMPLOYEE_NAME, DEPARTMENT_NAME, BASIC)
	SELECT EMPLOYEE.CODE, EMPLOYEE.NAME, ORGANIZATION.NAME, BASIC
		FROM EMPLOYEE, ORGANIZATION
		WHERE DEPARTMENT_CODE = ORGANIZATION.CODE
			AND BASIC = 20000
			AND ORGANIZATION.NAME = 'D1';

INSERT INTO MONEY(CODE, EMPLOYEE_NAME, DEPARTMENT_NAME, BASIC)
	SELECT EMPLOYEE.CODE, EMPLOYEE.NAME, ORGANIZATION.NAME, BASIC
		FROM EMPLOYEE, ORGANIZATION
		WHERE DEPARTMENT_CODE = ORGANIZATION.CODE
			AND BASIC >= 7000;

ALTER TABLE MONEY
	ADD NET INTEGER;

UPDATE MONEY
	SET NET = 1.5 * BASIC;

ALTER TABLE MONEY
	DROP COLUMN NET;

#DROP TABLE ORGANIZATION;
#DROP TABLE EMPLOYEE;
#DROP TABLE LEAVES;
#DROP TABLE MONEY;
