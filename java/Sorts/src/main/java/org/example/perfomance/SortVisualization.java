package org.example.perfomance;

import org.example.sorter.SorterService;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class SortVisualization {

    private static final int PANEL_WIDTH = 800;
    private static final int PANEL_HEIGHT = 500;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SortVisualization::createAndShowGUI);
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("Визуализация работы сортировок");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(PANEL_WIDTH, PANEL_HEIGHT);

        SortPanel panel = new SortPanel();
        frame.add(panel);

        frame.setVisible(true);
    }
}

class SortPanel extends JPanel {

    private final JTextField inputField;
    private final JButton startButton;
    private final JButton pauseButton;
    private final JButton nextButton;
    private final JButton prevButton;
    private final JComboBox<String> algorithmSelector;

    private ArrayList<ArrayList<Integer>> steps;
    private int currentStep = 0;
    private Timer timer;
    private boolean isPaused = true;

    private int highlightIndex1 = -1;
    private int highlightIndex2 = -1;

    public SortPanel() {
        this.setLayout(new BorderLayout());

        JPanel controlPanel = new JPanel();
        inputField = new JTextField(30);
        inputField.setText("5,2,8,1,3");

        algorithmSelector = new JComboBox<>(new String[]{"bubble", "quick", "merge", "heap", "insertion"});
        startButton = new JButton("Старт");
        pauseButton = new JButton("Пауза");
        nextButton = new JButton("Шаг вперед");
        prevButton = new JButton("Шаг назад");

        controlPanel.add(new JLabel("Ввод массива:"));
        controlPanel.add(inputField);
        controlPanel.add(new JLabel("Выбор алгоритма:"));
        controlPanel.add(algorithmSelector);
        controlPanel.add(startButton);
        controlPanel.add(pauseButton);
        controlPanel.add(prevButton);
        controlPanel.add(nextButton);

        this.add(controlPanel, BorderLayout.NORTH);

        startButton.addActionListener(e -> startSorting());
        pauseButton.addActionListener(e -> togglePause());
        nextButton.addActionListener(e -> showNextStep());
        prevButton.addActionListener(e -> showPreviousStep());
    }

    private void startSorting() {
        try {
            String[] inputStrings = inputField.getText().split(",");
            List<Integer> inputData = new ArrayList<>();
            for (String s : inputStrings) {
                inputData.add(Integer.parseInt(s.trim()));
            }

            String algorithm = (String) algorithmSelector.getSelectedItem();
            steps = SorterService.sortStepByStep(inputData, algorithm);
            currentStep = 0;
            isPaused = false;

            if (timer != null && timer.isRunning()) {
                timer.stop();
            }

            timer = new Timer(500, e -> {
                if (!isPaused) {
                    if (currentStep < steps.size() - 1) {
                        highlightIndexesForStep(currentStep, currentStep + 1);
                        currentStep++;
                        repaint();
                    } else {
                        ((Timer) e.getSource()).stop();
                    }
                }
            });
            timer.start();

            repaint();
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "Invalid input");
        }
    }

    private void togglePause() {
        isPaused = !isPaused;
    }

    private void showNextStep() {
        if (steps != null && currentStep < steps.size() - 1) {
            highlightIndexesForStep(currentStep, currentStep + 1);
            currentStep++;
            repaint();
        }
    }

    private void showPreviousStep() {
        if (steps != null && currentStep > 0) {
            currentStep--;
            highlightIndexesForStep(currentStep, currentStep + 1);
            repaint();
        }
    }

    private void highlightIndexesForStep(int step1, int step2) {
        if (step1 < 0 || step2 >= steps.size()) {
            highlightIndex1 = -1;
            highlightIndex2 = -1;
            return;
        }

        List<Integer> array1 = steps.get(step1);
        List<Integer> array2 = steps.get(step2);

        highlightIndex1 = -1;
        highlightIndex2 = -1;
        for (int i = 0; i < array1.size(); i++) {
            if (!array1.get(i).equals(array2.get(i))) {
                if (highlightIndex1 == -1) {
                    highlightIndex1 = i;
                } else {
                    highlightIndex2 = i;
                    break;
                }
            }
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (steps == null || steps.isEmpty()) return;

        List<Integer> currentData = steps.get(currentStep);

        int panelWidth = getWidth();
        int panelHeight = getHeight() - 50;
        int cellWidth = panelWidth / currentData.size();
        int cellHeight = Math.min(cellWidth, panelHeight / 2);

        for (int i = 0; i < currentData.size(); i++) {
            int x = i * cellWidth;
            int y = (panelHeight - cellHeight) / 2;
            if (i == highlightIndex1 || i == highlightIndex2) {
                g.setColor(Color.RED);
            } else {
                g.setColor(Color.LIGHT_GRAY);
            }
            g.fillRect(x, y, cellWidth, cellHeight);
            g.setColor(Color.BLACK);
            g.drawRect(x, y, cellWidth, cellHeight);
            String value = String.valueOf(currentData.get(i));
            FontMetrics fm = g.getFontMetrics();
            int textWidth = fm.stringWidth(value);
            int textHeight = fm.getHeight();

            int textX = x + (cellWidth - textWidth) / 2;
            int textY = y + (cellHeight + textHeight) / 2 - fm.getDescent();
            g.drawString(value, textX, textY);
        }
        g.setColor(Color.BLACK);
        g.drawString("Step: " + (currentStep + 1) + " / " + steps.size(), 10, panelHeight + 20);
    }
}
