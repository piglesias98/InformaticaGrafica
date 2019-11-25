void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());
	for (unsignes long i=0; i<caras.size(); i++){
		//obtener dos vectores en el triangulo y calcular el producto vectorial
		_vertex3f a1=vertices[caras[i]._1].vertices[caras[i].0_];
		_vertex3f a2=vertices[caras[i]._2].vertices[caras[i].0_];
		n=a1.cross_product(a2);
		//modulo
		float m=sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
		//normalización
		normales_caras[i]= _vertex3f(n.x/m, n.y/m, n.z/m);
	}
	b_normales_caras=true;
}
