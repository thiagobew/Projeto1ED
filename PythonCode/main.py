from MatrixReader import MatrixReader

matrix = [
    [1, 0, 1, 0, 0],
    [1, 0, 1, 0, 1],
    [0, 0, 0, 0, 0],
    [1, 1, 1, 0, 1]
]


reader = MatrixReader(matrix)
print(reader.componentsQuant)


