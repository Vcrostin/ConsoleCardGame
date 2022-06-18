DROP TABLE card_gen;

CREATE TABLE card_gen(
    card_id INT PRIMARY KEY AUTO_INCREMENT,
    base_class VARCHAR(50),
    new_class VARCHAR(50),
    args JSON DEFAULT NULL
    );

SELECT * from card_gen;

INSERT INTO card_gen (base_class, new_class, args)
VALUES ("UnitCard", "Unit", '[1, 1, 1, "COMMON"]')

