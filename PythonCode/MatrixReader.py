class MatrixReader:
    def __init__(self, matrix: list) -> None:
        self.__matrix = matrix
        self.__rows = len(matrix)
        self.__columns = len(matrix[0])
        self.__active_char = 1
        self.__closed_nodes = []
        self.__componentsQuant = self.__getComponentsQuant()

    @property
    def componentsQuant(self) -> int:
        return self.__componentsQuant

    def __getComponentsQuant(self) -> int:
        quant = 0

        for row in range(self.__rows):
            for column in range(self.__columns):
                if self.__isActivePosition((row, column)):
                    if (row, column) not in self.__closed_nodes:
                        self.__processPoint((row, column))
                        quant += 1

        return quant

    def __processPoint(self, position: tuple) -> None:
        open_nodes = [position]
        while len(open_nodes) > 0:
            current = open_nodes.pop(0)
            neighbour_nodes = self.__getActiveNeighbors(current)

            for neighbour in neighbour_nodes:
                if neighbour not in open_nodes and neighbour not in self.__closed_nodes:
                    open_nodes.append(neighbour)

            self.__closed_nodes.append(current)

    def __getActiveNeighbors(self, position: tuple) -> list:
        neighbors = []
        side_positions = [(1, 0), (0, 1), (0, -1), (-1, 0)]

        for side in side_positions:
            neighbour_pos = (side[0]+position[0], side[1]+position[1])
            if self.__isValidPosition(neighbour_pos) and self.__isActivePosition(neighbour_pos):
                neighbors.append(neighbour_pos)

        return neighbors

    def __isActivePosition(self, position: tuple) -> bool:
        return self.__matrix[position[0]][position[1]] == self.__active_char

    def __isValidPosition(self, position: tuple) -> bool:
        if position[0] < 0 or position[0] >= self.__rows:
            return False
        if position[1] < 0 or position[1] >= self.__columns:
            return False
        return True


if __name__ == '__main__':
    matrix1 = [
        [1, 0, 1, 0, 0],
        [1, 0, 1, 0, 1],
        [0, 0, 0, 0, 0],
        [1, 1, 1, 0, 1]
    ]
    matrix2 = [
        [1, 1, 1, 0, 0],
        [1, 1, 1, 0, 1],
        [1, 1, 0, 0, 0],
        [1, 1, 0, 0, 1]
    ]

    reader1 = MatrixReader(matrix1)
    reader2 = MatrixReader(matrix2)
    print(f'Should be 5 | Value: {reader1.componentsQuant}')
    print(f'Should be 3 | Value: {reader2.componentsQuant}')
