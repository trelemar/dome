foreign class Transform {
	construct init() {}
	construct initFromFile(path) {
		f_loadFromFile(path)
	}
	foreign f_loadFromFile(path)

	static loadFromFile(path) {
		return Transform.initFromFile(path)
	}
	
	foreign width
	foreign height

	foreign draw(x, y)
	foreign rdraw(x, y, map)
}