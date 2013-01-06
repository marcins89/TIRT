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
        
        AC : SizeControl {
        	@display("p=150,150");
        };
        
        SCH : FIFOScheduler {
            @display("p=350,150");
        };
        
        PRF : TokenBucket {
          	@display("p=250,150");  
        };
        
        sink: Node {
        	@display("p=450,150");
        };

    connections:
        
        OnOff.out --> AC.in++;
        poissonGenerator.out --> AC.in++;
        MMPPGenerator.out --> AC.in++;
        AC.out --> PRF.in;
        PRF.out --> SCH.in++;
        SCH.out --> sink.in;
    
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
        
        AC : BannedIp {
        	@display("p=150,150");
        };
        
        SCH : RRScheduler {
            @display("p=350,150");
        };
        
        PRF : DoubleTokenBucket {
          	@display("p=250,150");  
        };
        
        sink: Node {
        	@display("p=450,150");
        };

    connections:
        
        OnOff.out --> AC.in++;
        poissonGenerator.out --> AC.in++;
        MMPPGenerator.out --> AC.in++;
        AC.out --> PRF.in;
        PRF.out --> SCH.in++;
        SCH.out --> sink.in;
    
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
        
        AC : BufforControl {
        	@display("p=150,150");
        };
        
        SCH : WRRScheduler {
            @display("p=350,150");
        };
        
        PRF : LeakyBucket {
          	@display("p=250,150");  
        };
        
        sink: Node {
        	@display("p=450,150");
        };

    connections:
        
        OnOff.out --> AC.in++;
        poissonGenerator.out --> AC.in++;
        MMPPGenerator.out --> AC.in++;
        AC.out --> PRF.in;
        PRF.out --> SCH.in++;
        SCH.out --> sink.in;
    
}

