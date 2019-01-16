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