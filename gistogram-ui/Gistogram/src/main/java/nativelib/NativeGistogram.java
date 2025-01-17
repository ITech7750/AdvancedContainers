package nativelib;

import java.util.List;

/**
 * A Java interface for interacting with the native Gistogram implementation.
 */
public class NativeGistogram {

    /**
     * Adds a parameter to the native Gistogram.
     *
     * @param parameter the parameter to add
     */
    public native void addParameter(String parameter);

    /**
     * Adds data to the native Gistogram.
     *
     * @param data the data to add
     */
    public native void addData(int data);

    /**
     * Retrieves the most frequent data point from the native Gistogram.
     *
     * @return the most frequent data point
     */
    public native int getMostFrequent();

    /**
     * Counts the number of data points within the specified range.
     *
     * @param lowerBound the lower bound of the range
     * @param upperBound the upper bound of the range
     * @return the count of data points in the range
     */
    public native int countInRange(int lowerBound, int upperBound);

    /**
     * Clears all data and parameters in the native Gistogram.
     */
    public native void clearAll();

    /**
     * Finds matching values in the Gistogram based on a condition.
     * The condition must be implemented in Java and passed as a lambda or functional interface.
     *
     * @param condition the condition to match
     * @return a list of matching values
     */
    public native List<Integer> findMatchingValues(String condition);

    static {
        try {
            System.load("/home/itech/Desktop/University/AdvancedContainers/cmake-build-debug/libGistogramLibrary.so");
            System.out.println("Native Gistogram library loaded successfully.");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native Gistogram library: " + e.getMessage());
            throw new RuntimeException("Could not load native library", e);
        }
    }
}
