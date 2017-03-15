package com.fyber.mediation;

import android.app.Activity;
import com.fyber.mediation.adcolony.AdColonyMediationAdapter;
import com.fyber.mediation.unityads.UnityAdsMediationAdapter;
import com.fyber.utils.FyberLogger;
import java.lang.InterruptedException;
import java.lang.Object;
import java.lang.String;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

public final class MediationAdapterStarter {
  private static final String TAG = "MediationAdapterStarter";

  public static AdaptersListener adaptersListener;

  private static void startApplifier(final Activity activity, final Map<String, Object> configs, final Map<String, MediationAdapter> map) {
    try {
      MediationAdapter adapter = new UnityAdsMediationAdapter();
      FyberLogger.d(TAG, "Starting adapter Applifier with version 2.0.5-r1");
      if (adapter.startAdapter(activity, configs)) {
        FyberLogger.d(TAG, "Adapter Applifier with version 2.0.5-r1 was started successfully");
        map.put("applifier", adapter);
      } else {
        FyberLogger.d(TAG, "Adapter Applifier with version 2.0.5-r1 was not started successfully");
      }
    } catch (Throwable throwable) {
      FyberLogger.e(TAG, "Exception occurred while loading adapter Applifier with version 2.0.5-r1 - " + throwable.getCause());
    }
  }

  private static void startAdColony(final Activity activity, final Map<String, Object> configs, final Map<String, MediationAdapter> map) {
    try {
      MediationAdapter adapter = new AdColonyMediationAdapter();
      FyberLogger.d(TAG, "Starting adapter AdColony with version 3.1.0-r1");
      if (adapter.startAdapter(activity, configs)) {
        FyberLogger.d(TAG, "Adapter AdColony with version 3.1.0-r1 was started successfully");
        map.put("adcolony", adapter);
      } else {
        FyberLogger.d(TAG, "Adapter AdColony with version 3.1.0-r1 was not started successfully");
      }
    } catch (Throwable throwable) {
      FyberLogger.e(TAG, "Exception occurred while loading adapter AdColony with version 3.1.0-r1 - " + throwable.getCause());
    }
  }

  public static Map<String, MediationAdapter> startAdapters(final Activity activity, final Map<String, Map<String, Object>> configs) {
    Map<String, MediationAdapter> map = new HashMap<>();
    startApplifier(activity, getConfigsForAdapter(configs, "Applifier"), map);
    startAdColony(activity, getConfigsForAdapter(configs, "AdColony"), map);
    return map;
  }

  public static int getAdaptersCount() {
    return 1;
  }

  private static Map<String, Object> getConfigsForAdapter(Map<String, Map<String, Object>> configs, String adapter) {
    Map<String, Object> config = configs.get(adapter.toLowerCase());
    if (config == null) {
      config = Collections.emptyMap();
    }
    return config;
  }

  private static Map<String, Map<String, Object>> getConfigs(final Future<Map<String, Map<String, Object>>> futureConfig) {
    Map<String, Map<String, Object>> configs = MediationConfigProvider.getConfigs();
    Map<String, Map<String, Object>> runtimeConfigs = MediationConfigProvider.getRuntimeConfigs();
    configs = mergeConfigs(runtimeConfigs, configs);
    try {
      if (futureConfig != null) {
        Map<String, Map<String, Object>> serverConfigs = futureConfig.get();
        configs = mergeConfigs(configs, serverConfigs);
      }
    } catch (InterruptedException | ExecutionException e) {
      FyberLogger.e(TAG, "Exception occurred", e);
    }
    return configs;
  }

  private static Map<String, Map<String, Object>> mergeConfigs(final Map<String, Map<String, Object>> fromConfigs, final Map<String, Map<String, Object>> intoConfigs) {
    if (fromConfigs != null && !fromConfigs.isEmpty()) {
      for (Map.Entry<String, Map<String, Object>> entry: fromConfigs.entrySet()) {
        String network = entry.getKey();
        Map<String, Object> adapterFromConfigs = entry.getValue();
        Map<String, Object> adapterIntoConfigs = intoConfigs.get(network);
        if (adapterIntoConfigs == null) {
          adapterIntoConfigs = new HashMap<>();
        }
        if (adapterFromConfigs != null) {
          adapterIntoConfigs.putAll(adapterFromConfigs);
        }
        intoConfigs.put(network, adapterIntoConfigs);
      }
    } else {
      FyberLogger.d(TAG, "There were no configurations to override");
    }
    return intoConfigs;
  }

  public static Map<String, MediationAdapter> startAdapters(final Activity activity, final Future<Map<String, Map<String, Object>>> future) {
    Map<String, Map<String, Object>> configs = getConfigs(future);
    Map<String, MediationAdapter> adapters = startAdapters(activity, configs);
    if (adaptersListener != null) {
      adaptersListener.startedAdapters(adapters.keySet(), configs);
    }
    return adapters;
  }
}
