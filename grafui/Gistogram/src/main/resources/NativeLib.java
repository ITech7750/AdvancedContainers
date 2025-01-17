package com.tech.nativelib;

public class NativeLib {

    /**
     * Returns a greeting message from native code.
     */
    public native String stringFromJNI();

    /**
     * Builds logistic data.
     */
    public native void buildLogistic(
            String resultFilePath,
            int cityAmount,
            int roadAmount,
            int cargo
    );

    /**
     * Builds logistic data from a file.
     */
    public native void buildLogisticFromFile(
            String dataFilePath,
            String resultFilePath,
            String startCity,
            String endCity,
            int cargo
    );

    /**
     * Builds logistic vertex data.
     */
    public native void buildLogisticVertex(
            String resultFilePath,
            int cityAmount,
            int roadAmount
    );

    /**
     * Builds logistic vertex data from a file.
     */
    public native void buildLogisticFromFileVertex(
            String dataFilePath,
            String resultFilePath,
            String startCity,
            String endCity
    );

    /**
     * Builds undirected logistic data.
     */
    public native void buildLogisticUndirected(
            String resultFilePath,
            int cityAmount,
            int roadAmount,
            int cargo
    );

    /**
     * Builds undirected logistic data from a file.
     */
    public native void buildLogisticFromFileUndirected(
            String dataFilePath,
            String resultFilePath,
            String startCity,
            String endCity,
            int cargo
    );

    /**
     * Builds undirected logistic vertex data.
     */
    public native void buildLogisticVertexUndirected(
            String resultFilePath,
            int cityAmount,
            int roadAmount
    );

    /**
     * Builds undirected logistic vertex data from a file.
     */
    public native void buildLogisticFromFileVertexUndirected(
            String dataFilePath,
            String resultFilePath,
            String startCity,
            String endCity
    );

    /**
     * Builds a histogram based on input parameters.
     */
    public native void buildGistogram(
            String path,
            String option,
            int amount,
            int enableStatistic,
            int filter1,
            int filter2,
            int filter3,
            int filter4,
            int birthYear,
            String cityStartsWith
    );

    /**
     * Builds a histogram from a file.
     */
    public native void buildGistogramFromFile(
            String path,
            String filePath,
            String option,
            int amount,
            int enableStatistic,
            int filter1,
            int filter2,
            int filter3,
            int filter4,
            int birthYear,
            String cityStartsWith
    );

    /**
     * Builds a bag structure with given constraints.
     */
    public native void buildBag(
            String path,
            int amount,
            int maxCapacity,
            int maxVolume
    );

    static {
        String libraryPath = System.getenv("NATIVE_LIB_PATH");
        if (libraryPath == null) {
            libraryPath = "/home/itech/Desktop/University/AdvancedContainers/api/Gistogram/libNativeLib.so";
        }

        try {
            System.load(libraryPath);
            System.out.println("Native library loaded successfully from " + libraryPath);
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native library: " + e.getMessage());
            throw new RuntimeException("Could not load native library", e);
        }
    }
}
