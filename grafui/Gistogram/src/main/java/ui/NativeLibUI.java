package ui;

import data.City;
import data.Road;
import com.tech.nativelib.NativeLib;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class NativeLibUI {

    private final NativeLib nativeLib;
    private final List<City> cities;
    private final List<Road> roads;

    public NativeLibUI(NativeLib nativeLib) {
        this.nativeLib = nativeLib;
        this.cities = new ArrayList<>();
        this.roads = new ArrayList<>();
        initUI();
    }

    private void initUI() {
        JFrame frame = new JFrame("Logistic Builder");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(new BorderLayout());

        JTabbedPane tabbedPane = new JTabbedPane();

        JPanel cityPanel = createCityPanel();
        tabbedPane.addTab("Города", cityPanel);

        JPanel roadPanel = createRoadPanel();
        tabbedPane.addTab("Дороги", roadPanel);

        JPanel logisticPanel = createLogisticPanel();
        tabbedPane.addTab("Логистика", logisticPanel);

        JPanel graphPanel = createGraphPanel();
        tabbedPane.addTab("Граф", graphPanel);

        frame.add(tabbedPane, BorderLayout.CENTER);
        frame.setVisible(true);
    }

    private JPanel createCityPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2, 10, 10));

        JLabel idLabel = new JLabel("ID Города:");
        JTextField idField = new JTextField();
        JLabel nameLabel = new JLabel("Название города:");
        JTextField nameField = new JTextField();
        JLabel cargoLabel = new JLabel("Cargo to Drop:");
        JTextField cargoField = new JTextField();
        JLabel xLabel = new JLabel("X координата:");
        JTextField xField = new JTextField();
        JLabel yLabel = new JLabel("Y координата:");
        JTextField yField = new JTextField();

        JButton addButton = new JButton("Добавить город");
        addButton.addActionListener(e -> {
            try {
                long id = Long.parseLong(idField.getText());
                String name = nameField.getText();
                int cargo = Integer.parseInt(cargoField.getText());
                float x = Float.parseFloat(xField.getText());
                float y = Float.parseFloat(yField.getText());

                City city = new City(id, name, cargo, x, y);
                cities.add(city);
                JOptionPane.showMessageDialog(panel, "City added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);

                idField.setText("");
                nameField.setText("");
                cargoField.setText("");
                xField.setText("");
                yField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(panel, "Invalid input!", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });

        panel.add(idLabel);
        panel.add(idField);
        panel.add(nameLabel);
        panel.add(nameField);
        panel.add(cargoLabel);
        panel.add(cargoField);
        panel.add(xLabel);
        panel.add(xField);
        panel.add(yLabel);
        panel.add(yField);
        panel.add(new JLabel());
        panel.add(addButton);

        return panel;
    }

    private JPanel createRoadPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(7, 2, 10, 10));

        JLabel idLabel = new JLabel("ID Дороги:");
        JTextField idField = new JTextField();
        JLabel nameLabel = new JLabel("Название дороги:");
        JTextField nameField = new JTextField();
        JLabel lengthLabel = new JLabel("Протяженность:");
        JTextField lengthField = new JTextField();
        JLabel speedLabel = new JLabel("Максимальная скорость:");
        JTextField speedField = new JTextField();
        JLabel startCityLabel = new JLabel("Город начала дорги (ID):");
        JTextField startCityField = new JTextField();
        JLabel endCityLabel = new JLabel("Город конца дорги ID:");
        JTextField endCityField = new JTextField();

        JButton addButton = new JButton("Добавить дорогу");
        addButton.addActionListener(e -> {
            try {
                long id = Long.parseLong(idField.getText());
                String name = nameField.getText();
                String length = lengthField.getText();
                String maxSpeed = speedField.getText();
                long startCityId = Long.parseLong(startCityField.getText());
                long endCityId = Long.parseLong(endCityField.getText());

                City startCity = findCityById(startCityId);
                City endCity = findCityById(endCityId);

                if (startCity == null || endCity == null) {
                    JOptionPane.showMessageDialog(panel, "Invalid city IDs!", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                Road road = new Road(id, name, length, maxSpeed, startCity, endCity);
                roads.add(road);
                JOptionPane.showMessageDialog(panel, "Road added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);

                idField.setText("");
                nameField.setText("");
                lengthField.setText("");
                speedField.setText("");
                startCityField.setText("");
                endCityField.setText("");
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(panel, "Invalid input!", "Error", JOptionPane.ERROR_MESSAGE);
            }
        });

        panel.add(idLabel);
        panel.add(idField);
        panel.add(nameLabel);
        panel.add(nameField);
        panel.add(lengthLabel);
        panel.add(lengthField);
        panel.add(speedLabel);
        panel.add(speedField);
        panel.add(startCityLabel);
        panel.add(startCityField);
        panel.add(endCityLabel);
        panel.add(endCityField);
        panel.add(new JLabel());
        panel.add(addButton);

        return panel;
    }

    private JPanel createLogisticPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 1, 10, 10));

        JButton logisticButton = new JButton("Построить логистику");
        logisticButton.addActionListener(e -> {
            String filePath = JOptionPane.showInputDialog(panel, "Путь к файлу с результатом:");
            if (filePath != null && !filePath.isEmpty()) {
                nativeLib.buildLogistic(filePath, cities.size(), roads.size(), 100);
                JOptionPane.showMessageDialog(panel, "Logistic data built successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
            }
        });

        panel.add(logisticButton);

        return panel;
    }

    private JPanel createGraphPanel() {
        JPanel panel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                for (Road road : roads) {
                    City start = road.getStart();
                    City end = road.getEnd();

                    int startX = (int) start.getX();
                    int startY = (int) start.getY();
                    int endX = (int) end.getX();
                    int endY = (int) end.getY();

                    g.drawLine(startX, startY, endX, endY);
                }

                for (City city : cities) {
                    int x = (int) city.getX();
                    int y = (int) city.getY();
                    g.fillOval(x - 5, y - 5, 10, 10);
                    g.drawString(city.getName(), x + 5, y - 5);
                }
            }
        };
        return panel;
    }

    private City findCityById(long id) {
        return cities.stream().filter(city -> city.getId() == id).findFirst().orElse(null);
    }

    public static void main(String[] args) {
        new NativeLibUI(new NativeLib());
    }
}
