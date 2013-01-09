//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package tirtproject.Networks;
import tirtproject.Generators.*;
import tirtproject.AdmissionControl.*;
import tirtproject.Profilers.*;
import tirtproject.Schedulers.*;

network networkA {
   
       submodules:
        OnOff: OnOffGenerator {
        	@display("p=50,50");
        };
        
        poissonGenerator: PoissonGenerator {
        	@display("p=50,150");
        };
        
        MMPPGenerator: MMPPGenerator {
        	@display("p=50,250");
        };
        
        AdmissionControl : SizeControl {
        	@display("p=150,150");
        };
        
        Scheduler : FIFOScheduler {
            @display("p=350,150");
        };
        
        Profiler : TokenBucket {
          	@display("p=250,150");  
        };
        
        sink: Node {
        	@display("p=450,150");
        };

    connections:
        
        OnOff.out --> AdmissionControl.in++;
        poissonGenerator.out --> AdmissionControl.in++;
        MMPPGenerator.out --> AdmissionControl.in++;
        AdmissionControl.out --> Profiler.in;
        Profiler.out --> Scheduler.in++;
        Scheduler.out --> sink.in;
    
}

network networkB {
   
       submodules:
        OnOff: OnOffGenerator {
        	@display("p=50,50");
        };
        
        poissonGenerator: PoissonGenerator {
        	@display("p=50,150");
        };
        
        MMPPGenerator: MMPPGenerator {
        	@display("p=50,250");
        };
        
        AdmissionControl : BannedIp {
        	@display("p=150,150");
        };
        
        Scheduler : RRScheduler {
            @display("p=350,150");
        };
        
        Profiler : DoubleTokenBucket {
          	@display("p=250,150");  
        };
        
        sink: Node {
        	@display("p=450,150");
        };

    connections:
        
        OnOff.out --> AdmissionControl.in++;
        poissonGenerator.out --> AdmissionControl.in++;
        MMPPGenerator.out --> AdmissionControl.in++;
        AdmissionControl.out --> Profiler.in;
        Profiler.out --> Scheduler.in++;
        Scheduler.out --> sink.in;
    
}

network networkC {
   
       submodules:
        OnOff: OnOffGenerator {
        	@display("p=50,50");
        };
        
        poissonGenerator: PoissonGenerator {
        	@display("p=50,150");
        };
        
        MMPPGenerator: MMPPGenerator {
        	@display("p=50,250");
        };
        
        AdmissionControl : BufforControl {
        	@display("p=150,150");
        };
        
        Scheduler : WRRScheduler {
            @display("p=350,150");
        };
        
        Profiler : LeakyBucket {
          	@display("p=250,150");  
        };
        
        sink: Node {
        	@display("p=450,150");
        };

    connections:
        
        OnOff.out --> AdmissionControl.in++;
        poissonGenerator.out --> AdmissionControl.in++;
        MMPPGenerator.out --> AdmissionControl.in++;
        AdmissionControl.out --> Profiler.in;
        Profiler.out --> Scheduler.in++;
        Scheduler.out --> sink.in;
    
}

