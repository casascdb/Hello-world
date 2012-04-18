import org.mixim.base.connectionManager.ConnectionManager;
import org.mixim.base.modules.BaseWorldUtility;


module Sim
{
    parameters:
        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
        double numHosts; // total number of hosts in the network  
        
        @display("bgb=$playgroundSizeX,$playgroundSizeY,white,,;bgp=10,50");      

    submodules:
        world: BaseWorldUtility {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                playgroundSizeZ = playgroundSizeZ;
                @display("p=100,0;i=misc/globe");

        }
        channelcontrol: ConnectionManager {
            parameters:
            	@display("p=200,0;b=42,42,rect,yellow,,;i=abstract/multicast");
        }
        host[numHosts]: Host {
            @display("p=20,20;b=42,42,rect,yellow,,;i=device/wifilaptop");
        }

    connections allowunconnected:
    // all connections and gates are to be generated dynamically

}




network sim extends Sim
{
    parameters:

}
