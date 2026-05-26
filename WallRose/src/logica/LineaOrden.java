package logica;

import java.io.Serializable;

public class LineaOrden implements Serializable {
	private Double cantidad;
	private Producto producto;

	public LineaOrden(Double cantidad, Producto producto) {
		this.cantidad = cantidad;
		this.producto = producto;
	}
	
	public Double getCantidad() {
		return cantidad;
	}
	
	public void setCantidad(Double cantidad) {
		this.cantidad = cantidad;
	}
	
	public Producto getProducto() {
		return producto;
	}
	
	public void setProducto(Producto producto) {
		this.producto = producto;
	}
	
	public Double calcularCosto() {
		return cantidad * producto.getPrecio();
	}
}
