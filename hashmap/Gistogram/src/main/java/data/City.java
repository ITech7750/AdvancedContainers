package data;

public class City {

    private long id;
    private String name;
    private int cargoToDrop;
    private float x;
    private float y;

    public City() {
        this(0, "", 0, 0f, 0f);
    }

    public City(long id, String name, int cargoToDrop, float x, float y) {
        this.id = id;
        this.name = name;
        this.cargoToDrop = cargoToDrop;
        this.x = x;
        this.y = y;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCargoToDrop() {
        return cargoToDrop;
    }

    public void setCargoToDrop(int cargoToDrop) {
        this.cargoToDrop = cargoToDrop;
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    @Override
    public String toString() {
        return "City{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", cargoToDrop=" + cargoToDrop +
                ", x=" + x +
                ", y=" + y +
                '}';
    }
}
