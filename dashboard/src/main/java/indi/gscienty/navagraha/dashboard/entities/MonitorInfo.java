package indi.gscienty.navagraha.dashboard.entities;

public class MonitorInfo {
   private String namespace;
   private boolean exist;
   private String serviceIP;

   public void setNamespace(String namespace) {
       this.namespace = namespace;
   }

   public String getNamespace() {
       return namespace;
   }

   public void setExist(boolean exist) {
       this.exist = exist;
   }

   public boolean getExist() {
       return exist;
   }

   public void setServiceIP(String serviceIP) {
       this.serviceIP = serviceIP;
   }

   public String getServiceIP() {
       return serviceIP;
   }
}
