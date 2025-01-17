package data;
import data.City;

public class Road {

    private long id;
    private String name;
    private String length;
    private String maxSpeed;
    private City start;
    private City end;

    public Road() {
        this(0, "", "", "", new City(), new City());
    }

    public Road(long id, String name, String length, String maxSpeed, City start, City end) {
        this.id = id;
        this.name = name;
        this.length = length;
        this.maxSpeed = maxSpeed;
        this.start = start;
        this.end = end;
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

    public String getLength() {
        return length;
    }

    public void setLength(String length) {
        this.length = length;
    }

    public String getMaxSpeed() {
        return maxSpeed;
    }

    public void setMaxSpeed(String maxSpeed) {
        this.maxSpeed = maxSpeed;
    }

    public City getStart() {
        return start;
    }

    public void setStart(City start) {
        this.start = start;
    }

    public City getEnd() {
        return end;
    }

    public void setEnd(City end) {
        this.end = end;
    }

    @Override
    public String toString() {
        return "Road{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", length='" + length + '\'' +
                ", maxSpeed='" + maxSpeed + '\'' +
                ", start=" + start +
                ", end=" + end +
                '}';
    }
}
