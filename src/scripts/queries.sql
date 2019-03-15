--DELETE FROM experiments WHERE id IN(
SELECT MAX(e.id), experiment_name, problem, random_seed, training_size, COUNT(*)
FROM experiments e LEFT JOIN parameters p ON e.id=p.parent
GROUP BY experiment_name, problem, random_seed, training_size
HAVING COUNT(*) > 1
--)
;

SELECT problem,  experiment_name, training_size, COUNT(*) FROM parameters
GROUP BY problem, experiment_name, training_size
HAVING COUNT(*) != 15
ORDER BY COUNT(*) ASC

;

SELECT
	p.training_size AS X,
	(CASE p.problem
		WHEN 'chvatal_diet' THEN 6
		WHEN 'facility_location' THEN 40
		WHEN 'queens1' THEN 8
		WHEN 'queens2' THEN 64
		WHEN 'queens3' THEN 64
		WHEN 'queens4' THEN 64
		WHEN 'queens5' THEN 64
		WHEN 'steinerbaum' THEN 7
		WHEN 'tsp' THEN 45 END) AS dimx,
	total_time AS time
FROM experiments e JOIN parameters p ON e.id=p.parent
JOIN generations g ON e.id=g.parent
WHERE  p.experiment_name = '700x3'
AND g.end=1
ORDER BY p.training_size

;

SELECT CASE WHEN machine LIKE 'lab-ci-%' OR machine LIKE 'lab-43-%' THEN 'Core i7-4790' ELSE 'Core i7-4770' END AS CPU,
COUNT(*) as 'count',
SUM(g.total_time) AS total_time
FROM experiments e JOIN parameters p ON e.id=p.parent
JOIN generations g ON e.id=g.parent
WHERE machine is not NULL AND g.end=1
GROUP BY 1;