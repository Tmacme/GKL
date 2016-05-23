package com.intel.gkl;

import org.apache.commons.io.FileUtils;
import org.apache.commons.io.FilenameUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;
import java.io.IOException;
import java.net.URL;

public class Utils {
    private final static Logger logger = LogManager.getLogger(Utils.class);
    private final static String GKL_LIB_NAME = "IntelGKL";
    private final static boolean isMac = System.getProperty("os.name", "unknown").toLowerCase().startsWith("mac");
    private static boolean isLoaded = false;

    public static synchronized boolean load(File tempDir) {
        if (isLoaded) { return true; }

        try {
            // try to load from library path
            System.loadLibrary(GKL_LIB_NAME);
            logger.info("Intel GKL library loaded from system library path.");
        } catch (UnsatisfiedLinkError ule) {
            try {
                // try to extract from jar file
                String filename = System.mapLibraryName(GKL_LIB_NAME);
                String jarPath = "native/" + (isMac ? "mac/64/" : "linux/64/");

                URL inputUrl = Utils.class.getResource(jarPath + filename);
                File temp = File.createTempFile(FilenameUtils.getBaseName(filename),
                        "." + FilenameUtils.getExtension(filename), tempDir);

                logger.debug("Extracted jar:%s%s to %s\n", jarPath, filename, temp.getAbsolutePath());

                FileUtils.copyURLToFile(inputUrl, temp);
                temp.deleteOnExit();
                System.load(temp.getAbsolutePath());
                logger.info("Intel GKL library loaded from jar file.");

            } catch (IOException ioe) {
                // not supported
                logger.warn("Unable to load Intel GKL library.");
                return false;
            }
        }

        isLoaded = true;
        return true;
    }

}
