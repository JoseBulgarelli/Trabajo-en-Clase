package logica;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Orden implements Serializable {
	private final Integer numero;
	private final LocalDate fecha;
	private EstadoOrden estado;
	private List<LineaOrden> lineas;
	private Cliente cliente;
	private final static Double IV = 0.13;
	
	public Orden(Integer numero, Cliente cliente) {
		this.cliente = cliente;
		this.numero = numero;
		this.fecha = LocalDate.now();
		this.estado = EstadoOrden.INICIADA;
		this.lineas = new ArrayList<LineaOrden>();
	}
	
	public EstadoOrden getEstado() {
		return estado;
	}
	
	public void setEstado(EstadoOrden estado) {
		this.estado = estado;
	}
	
	public Integer getNumero() {
		return numero;
	}
	
	public LocalDate getFecha() {
		return fecha;
	}
	
	public List<LineaOrden> getLineas() {
		return lineas;
	}
	
	public Cliente getCliente() {
		return cliente;		
	}
	
	public Double calcularMonto() {
		Double monto = 0.0;
		for (LineaOrden linea : lineas) {
			monto += linea.calcularCosto();
		}
		return monto;
	}
	
	public Double calcularMontoImpuesto() {
		return calcularMonto() * IV;		
	}
	
	public Double calcularMontoTotal() {
		return calcularMonto() + calcularMontoImpuesto();		
	}
	
	public void agregarLinea(LineaOrden linea) {
		lineas.add(linea);		
	}
	
	public void borrarLinea(int numeroLinea) throws Exception {
		if (numeroLinea < 0 || numeroLinea >= lineas.size())
			throw new Exception("Número de línea no válido.");
		lineas.remove(numeroLinea);
	}
	
	public int cantidadLineas() {
		return lineas.size();		
	}
	
	public LineaOrden getLinea(int numeroLinea) throws Exception {
		if (numeroLinea < 0 || numeroLinea >= lineas.size())
			throw new Exception("Número de línea no válido.");
		return lineas.get(numeroLinea);
	}
}
