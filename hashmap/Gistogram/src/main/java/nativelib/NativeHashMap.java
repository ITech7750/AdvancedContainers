package nativelib;

import java.util.ArrayList;
import java.util.List;

public class NativeHashMap {

    /**
     * Puts a key-value pair into the native HashMap.
     */
    public native void put(String key, String value);

    /**
     * Retrieves the value associated with a given key.
     */
    public native String get(String key);

    /**
     * Checks if the native HashMap contains the specified key.
     */
    public native boolean containsKey(String key);

    /**
     * Removes the value associated with a given key.
     */
    public native void remove(String key);

    /**
     * Returns the number of key-value pairs in the native HashMap.
     */
    public native int size();

    /**
     * Checks if the native HashMap is empty.
     */
    public native boolean isEmpty();

    /**
     * Retrieves all keys in the native HashMap.
     */
    public native List<String> getKeys();

    /**
     * Retrieves all values in the native HashMap.
     */
    public native List<String> getValues();

    /**
     * Clears all key-value pairs in the native HashMap.
     */
    public native void clear();
    static {
        try {
            System.load("/home/itech/Desktop/University/AdvancedContainers/cmake-build-debug/libHashMapLibrary.so");
            System.out.println("Native library loaded successfully.");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native library: " + e.getMessage());
            throw new RuntimeException("Could not load native library", e);
        }
    }

}
