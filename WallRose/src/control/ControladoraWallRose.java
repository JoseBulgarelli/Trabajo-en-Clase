package control;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import logica.Cliente;
import logica.Orden;
import logica.Producto;
import logica.LineaOrden;
import logica.EstadoOrden;

public class ControladoraWallRose implements Serializable {
	private static ControladoraWallRose instance = null; 
	private Integer consecutivoOrden;
	private Integer consecutivoProducto;
	private Map<String, Cliente> clientes;
	private Map<Integer, Orden> ordenes;
	private Map<Integer, Producto> productos;
	
	private ControladoraWallRose() {
		this.consecutivoOrden = 1;
		this.consecutivoProducto = 1;
		this.clientes = new TreeMap<String, Cliente>();
		this.ordenes = new TreeMap<Integer, Orden>();
		this.productos = new TreeMap<Integer, Producto>();
		/*try {
			this.crearCliente("1-1111-1111", "Samantha Carter", "samantha@sg1.com");
			this.crearCliente("2-2222-2222", "Daniel Jackson", "daniel@sg1.com");
			this.crearCliente("3-3333-3333", "Jack O'Neill", "jack@sg1.com");
			this.crearProducto("Arroz", 20.0, "kg", 900.0);
			this.crearProducto("Frijoles", 10.0, "kg", 1000.0);
			this.crearProducto("Harina", 12.5, "kg", 1080.0);
			this.crearOrdenVacia("1-1111-1111");
			this.agregarLineaOrden(1, 1, 1.0);
			this.agregarLineaOrden(1, 2, 1.0);
			this.agregarLineaOrden(1, 3, 1.0);
			this.crearOrdenVacia("1-1111-1111");
			this.agregarLineaOrden(2, 1, 2.0);
			this.agregarLineaOrden(2, 2, 2.0);
			this.agregarLineaOrden(2, 3, 2.0);
			this.establecerOrdenPendiente(2);
		}
		catch (Exception e) {
			System.out.println(e.toString());
		}*/
	}
	
	public static ControladoraWallRose getInstance() {
		if (instance == null)
			instance = new ControladoraWallRose();
		return instance;
	}
	
	public List<Cliente> obtenerListadoClientes() {
		List<Cliente> listadoClientes = new ArrayList<Cliente>();
		for (Map.Entry<String, Cliente> e : clientes.entrySet()) {
			listadoClientes.add(e.getValue());
		}
		return listadoClientes;
	}
	
	private void verificarClienteExistente(String idCliente) throws Exception {
		if (!clientes.containsKey(idCliente))
			throw new Exception("Cliente no encontrado.");
	}
	
	private void verificarClienteNoExistente(String idCliente) throws Exception {
		if (clientes.containsKey(idCliente))
			throw new Exception("Cliente duplicado.");
	}
	
	private boolean esEmailValido(String email) {
		Pattern p = Pattern.compile("^[a-zA-Z0-9_!#$%&’*+/=?`{|}~^.-]+@[a-zA-Z0-9.-]+$");
		Matcher m = p.matcher(email);
		return m.matches();
	}
	
	private void verificarEmail(String email) throws Exception {
		if (!esEmailValido(email))
			throw new Exception("Email no válido.");
	}
	
	private void verificarProductoExistente(Integer codigoProducto) throws Exception {
		if (!productos.containsKey(codigoProducto))
			throw new Exception("Producto no encontrado.");
	}

	private void verificarOrdenExistente(Integer numeroOrden) throws Exception  {
		if (!ordenes.containsKey(numeroOrden))
			throw new Exception("Orden no encontrada.");
	}
	
	private void verificarLineaOrdenExistente(Integer numeroOrden, Integer numeroLinea)
															 throws Exception {
		Orden orden = ordenes.get(numeroOrden);
		if (numeroLinea < 0 || numeroLinea >= orden.cantidadLineas())
			throw new Exception("Número de línea no válido.");
	}
	
	public Cliente obtenerCliente(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		return clientes.get(idCliente);
	}
	
	public List<Orden> obtenerListadoOrdenesCliente(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		Cliente c = clientes.get(idCliente);	
		List<Orden> listadoOrdenes = new ArrayList<Orden>();
		Map<Integer, Orden> ordenes = c.getOrdenes();
		for (Orden o : ordenes.values()) {
			listadoOrdenes.add(o);
		}
		return listadoOrdenes;
	}
	
	private List<Orden> obtenerListadoOrdenesPorEstado(String idCliente, EstadoOrden estado) {
		List<Orden> listadoOrdenes = new ArrayList<Orden>();
		for (Map.Entry<Integer, Orden> entry : ordenes.entrySet()) {
			Orden orden = entry.getValue();
			if (orden.getEstado() == estado)
				listadoOrdenes.add(orden);
		}
		return listadoOrdenes;		
	}
	
	public List<Orden> obtenerListadoOrdenesIniciadasCliente(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		return obtenerListadoOrdenesPorEstado(idCliente, EstadoOrden.INICIADA);
	}
	
	public List<Orden> obtenerListadoOrdenesPendientesCliente(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		return obtenerListadoOrdenesPorEstado(idCliente, EstadoOrden.PENDIENTE);
	}
	
	public List<Orden> obtenerListadoOrdenesTerminadasCliente(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		return obtenerListadoOrdenesPorEstado(idCliente, EstadoOrden.TERMINADA);
	}
	
	public void crearCliente(String idCliente, String nombre, String email) throws Exception{
		verificarClienteNoExistente(idCliente);
		verificarEmail(email);
		Cliente c = new Cliente(idCliente, nombre, email);
		clientes.put(idCliente, c);
	}
	
	public void actualizarCliente(String idCliente, String nombre, String email ) throws Exception {
		verificarClienteExistente(idCliente);
		verificarEmail(email);
		Cliente c = clientes.get(idCliente);
		c.setNombre(nombre);
		c.setEmail(email);
	}
	
	public void borrarCliente(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		Cliente c = clientes.get(idCliente);
		Map<Integer, Orden> ordenesCliente = c.getOrdenes();
		for (Integer numeroOrden : ordenesCliente.keySet()) {
			ordenes.remove(numeroOrden);
		}
		clientes.remove(idCliente);
	}
	
	public List<Producto> obtenerListadoProductos() {
		List<Producto> listadoProductos = new ArrayList<Producto>();
		for (Map.Entry<Integer, Producto> entry : productos.entrySet()) {
			listadoProductos.add(entry.getValue());
		}
		return listadoProductos;
	}
	
	public void crearProducto(String nombre, Double existencias, String unidad, Double precio) 
																			throws Exception {
		if (nombre.equals(""))
			throw new Exception("Nombre no puede ser vacío.");
		if (existencias < 0 || precio < 0)
			throw new Exception("El precio y existencias no pueden ser negativos.");
		Producto p = new Producto(consecutivoProducto, nombre, existencias, unidad, precio);
		productos.put(consecutivoProducto, p);
		consecutivoProducto++;
	}
	
	public Producto obtenerProducto(Integer codigoProducto) throws Exception {
		verificarProductoExistente(codigoProducto);
		Producto p = productos.get(codigoProducto);
		return p;
	}
	
	public void actualizarProducto(Integer codigoProducto, String nombre, 
			Double existencias, String unidad, Double precio) throws Exception {
		verificarProductoExistente(codigoProducto);
		Producto p = productos.get(codigoProducto);
		p.setNombre(nombre);
		p.setExistencias(existencias);
		p.setUnidad(unidad);
		p.setPrecio(precio);		
	}
	
	public void borrarProducto(Integer codigoProducto) throws Exception {
		verificarProductoExistente(codigoProducto);
		for (Orden orden : ordenes.values()) {
			for (LineaOrden linea : orden.getLineas()) {
				Producto producto = linea.getProducto();
				if (producto.getCodigo() == codigoProducto) {
					throw new Exception("El producto está siendo utilizado en la orden " 
										+ orden.getNumero() + ".");
				}				
			}
		}
		productos.remove(codigoProducto);
	}
	
	public boolean esProductoUtilizado(Integer codigoProducto) throws Exception {
		verificarProductoExistente(codigoProducto);
		Producto p = productos.get(codigoProducto);
		for (Orden o : obtenerListadoOrdenes()) {
			for (LineaOrden linea : o.getLineas()) {
				if (linea.getProducto() == p)
					return true;
			}
		}
		return false;
	}
	
	public List<Orden> obtenerListadoOrdenes() {
		List<Orden> listadoOrdenes = new ArrayList<Orden>();
		for (Orden orden : ordenes.values()) {
			listadoOrdenes.add(orden);
		}
		return listadoOrdenes;
	}
	
	public Double obtenerMontoTotalPendiente() {
		Double totalPendiente = 0.0;
		for (Orden orden : ordenes.values()) {
			if (orden.getEstado() == EstadoOrden.PENDIENTE) {
				totalPendiente += orden.calcularMontoTotal();
			}			
		}
		return totalPendiente;
	}
	
	public void crearOrdenVacia(String idCliente) throws Exception {
		verificarClienteExistente(idCliente);
		Cliente cliente = clientes.get(idCliente);
		Orden orden = new Orden(consecutivoOrden, cliente);
		ordenes.put(consecutivoOrden, orden);
		cliente.agregarOrden(orden);
		consecutivoOrden++;		
	}
	
	public Orden obtenerOrden(Integer numeroOrden) throws Exception {
		verificarOrdenExistente(numeroOrden);
		return ordenes.get(numeroOrden);
	} 
	
	public List<LineaOrden> obtenerLineasOrden(Integer numeroOrden) throws Exception {
		verificarOrdenExistente(numeroOrden);
		Orden orden = ordenes.get(numeroOrden);
		return orden.getLineas();
	}
	
	public void establecerOrdenPendiente(Integer numeroOrden) throws Exception  {
		verificarOrdenExistente(numeroOrden);
		Orden orden = ordenes.get(numeroOrden);
		orden.setEstado(EstadoOrden.PENDIENTE);
	}
	
	public void establecerOrdenTerminada(Integer numeroOrden) throws Exception {
		verificarOrdenExistente(numeroOrden);
		Orden orden = ordenes.get(numeroOrden);
		orden.setEstado(EstadoOrden.TERMINADA);
	}
	
	public void agregarLineaOrden(Integer numeroOrden, Integer codigoProducto, Double cantidad)
																		throws Exception {
		verificarOrdenExistente(numeroOrden);
		verificarProductoExistente(codigoProducto);
		if (cantidad < 0)
			throw new Exception("La cantidad no debe ser negativa.");
		Orden orden = ordenes.get(numeroOrden);
		Producto producto = productos.get(codigoProducto);
		LineaOrden linea = new LineaOrden(cantidad, producto);
		orden.agregarLinea(linea);
	}
	
	public void actualizarLineaOrden(Integer numeroOrden, Integer numeroLinea, 
									 Integer codigoProducto, Double cantidad) throws Exception {
		verificarOrdenExistente(numeroOrden);
		verificarLineaOrdenExistente(numeroOrden, numeroLinea);
		verificarProductoExistente(codigoProducto);
		Orden orden = ordenes.get(numeroOrden);
		Producto producto = productos.get(codigoProducto);
		LineaOrden linea = orden.getLinea(numeroLinea);
		linea.setProducto(producto);
		linea.setCantidad(cantidad);
	}
	
	public void borrarLineaOrden(Integer numeroOrden, Integer numeroLinea) throws Exception {
		verificarOrdenExistente(numeroOrden);
		verificarLineaOrdenExistente(numeroOrden, numeroLinea);
		Orden orden = ordenes.get(numeroOrden);
		orden.borrarLinea(numeroLinea);		
	}
	
	public void borrarOrden(Integer numeroOrden) throws Exception  {
		verificarOrdenExistente(numeroOrden);
		ordenes.remove(numeroOrden);
	}
	
	public static void guardarDatos() throws IOException {
		FileOutputStream file = new FileOutputStream("DatosWallRose.dat");
		ObjectOutputStream stream = new ObjectOutputStream(file);
		stream.writeObject(instance);
		stream.close();
		file.close();
	}
	
	public static void cargarDatos() throws IOException, ClassNotFoundException {
		FileInputStream file = new FileInputStream("DatosWallRose.dat");
		ObjectInputStream stream = new ObjectInputStream(file);
		instance = (ControladoraWallRose) stream.readObject();
		stream.close();
		file.close();
	}
}
